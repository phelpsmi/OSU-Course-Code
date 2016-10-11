<?php
session_start();
if($_SESSION['id'] != 'password'){
	header("Location: ../index");
}
$dbhost = 'oniddb.cws.oregonstate.edu';
$dbname = 'phelpsmi-db';
$dbuser = 'phelpsmi-db';
$dbpass = 'kPMlMYXHsXV0VOML';

$dbc = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname)
    or die("Error connecting to database server");

$playerId = $_GET['id'];


if($_POST['formSubmit'] == 'Submit') {

	$firstName = $_POST['firstName'];
	$lastName = $_POST['lastName'];
	$dob = $_POST['dob'];
	$team = $_POST['teamId'];
	$position = $_POST['position'];

	$errors = array();
	if(empty($firstName)){
		$errors[] = "First name missing";
	}
	if(empty($lastName)){
		$errors[] = "Last name missing";
	}
	if(empty($dob)){
		$errors[] = "Date of birth missing";
	} else if(!preg_match("/^[0-9]{4}-[0-9]{2}-[0-9]{2}$/", $dob)){
		$errors[] = "Date of birth not in proper date format";
	}
	if(empty($position)){
		$errors[] = "Player must have atleast one position";
	}

	if($errors){
		$message = 'The following errors occured in your form: \n';
		foreach ($errors as $e){
			$message .= $e;
			$message .= '\n';
		}
		echo "<SCRIPT> alert('$message'); </SCRIPT>";
	}
	else{
		$query = "UPDATE Player SET firstName = '${firstName}', lastName = '${lastName}', dob = '${dob}', teamId = ${team}
					WHERE playerId = $playerId ";
		$result = mysqli_query($dbc, $query) or die("Error querrying database $query");

		$query = "DELETE FROM PlayerPosition WHERE PlayerId = $playerId";

		$result = mysqli_query($dbc, $query) or die("error deleting stuff $query");

		foreach($position as $value){
			$query = "INSERT INTO PlayerPosition (positionId, playerId) ";
			$query .= "VALUES ('$value', $playerId)";
			$result = mysqli_query($dbc, $query) or die("Error inserting positions $query");
		}
		header("Location: view?id=$playerId");
		exit;


	}

}

$query = "SELECT * FROM Player WHERE playerId = $playerId";
$result = mysqli_query($dbc, $query) or die("error querrying database $query");
$player = mysqli_fetch_assoc($result);

?>
<head>
<title>New Player</title>
</head>

<body>

<a href="../main.php">Homepage</a><br>
<a href="index.php">Back to Index</a><br><br>

<form action="<?= htmlspecialchars($_SERVER['PHP_SELF']) . '?id=' . $playerId  ?>" method="POST">

First Name: 
<input type="text" name="firstName" value="<?= $player['firstName'] ?>"><br>
Last Name: 
<input type="text" name="lastName" value="<?= $player['lastName'] ?>"><br>
Date of Birth: 
<input type="text" name="dob" placeholder="YYYY-MM-DD" value="<?= $player['dob'] ?>"><br><br>

Team:
<select name='teamId'>
<option value='0'>FREE AGENT</option>

<?php
$query = "SELECT * FROM Team";
$result = mysqli_query($dbc, $query) or die("Error fetching teams");

while($team = mysqli_fetch_assoc($result)){
	if($team['teamId'] == $player['teamId']){
		echo "<option value='${team['teamId']}' selected='selected'>${team['name']}</option>";
	} else {
		echo "<option value='${team['teamId']}'>${team['name']}</option>";
	}
} 
?>

</select>
<br><br>

Position(s):<br>

<?php
$p_teams = ['Offense', 'Defense', 'Special Teams'];

$i = 0;
foreach ($p_teams as $p_team) {
	echo "${p_team}:<br>";
	$query = "SELECT * FROM Position WHERE team = '$p_team'";
	$result = mysqli_query($dbc, $query) or die("Error fetching positions $query");
	while($position = mysqli_fetch_assoc($result)){

		//checks for an association between the player and the position
		//if there is a relation, the checkbox will already be checked in the form
		$checked = '';
		$query = "SELECT * FROM PlayerPosition ";
		$query .= "WHERE playerId = ${playerId} AND positionId = '${position['positionId']}'";
		$playerposition = mysqli_query($dbc, $query) or die("Error fetching playerposition $query");
		if(mysqli_num_rows($playerposition) != 0){
			$checked = "checked='checked'";
		}
		
		echo "&nbsp;&nbsp;&nbsp;";
		echo "<input type='checkbox' name='position[$i]' value='${position['positionId']}' $checked >";
		echo "${position['name']}(${position['positionId']}): ";
		echo "<br>";
		$i++;

	}
}

?>

<input type="submit" name="formSubmit" value="Submit">

</form>

</body>