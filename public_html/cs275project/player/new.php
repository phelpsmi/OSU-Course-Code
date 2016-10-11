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
		$query = "INSERT INTO Player (firstName, lastName, dob, teamId) ";
		$query .= "VALUES ('$firstName', '$lastName', '$dob', $team)";
		$result = mysqli_query($dbc, $query) or die("Error querrying database $query");

		$query = "SELECT playerId from Player order by playerId DESC";
		$result = mysqli_query($dbc, $query) or die("Error finding player $query");
		$player = mysqli_fetch_assoc($result);
		$playerId = $player['playerId'];

		foreach($position as $value){
			$query = "INSERT INTO PlayerPosition (positionId, playerId) ";
			$query .= "VALUES ('$value', $playerId)";
			$result = mysqli_query($dbc, $query) or die("Error inserting positions $query");
		}


	}

}

?>
<head>
<title>New Player</title>
</head>

<body>

<a href="../main.php">Homepage</a><br>
<a href="index.php">Back to Index</a><br><br>

<form action="<?= htmlspecialchars($_SERVER['PHP_SELF']) ?>" method="POST">
First Name: <input type="text" name="firstName"><br>
Last Name: <input type="text" name="lastName"><br>
Date of Birth: <input type="text" name="dob" placeholder="YYYY-MM-DD"><br><br>

Team:
<select name='teamId'>
<option value='0'>FREE AGENT</option>

<?php
$query = "SELECT * FROM Team";
$result = mysqli_query($dbc, $query) or die("Error fetching teams");

while($team = mysqli_fetch_assoc($result)){
	echo "<option value='${team['teamId']}'>${team['name']}</option>";
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
		echo "&nbsp;&nbsp;&nbsp;";
		echo "<input type='checkbox' name='position[$i]' value='${position['positionId']}'>";
		echo "${position['name']}(${position['positionId']}): ";
		echo "<br>";
		$i++;

	}
}

?>

<input type="submit" name="formSubmit" value="Submit">

</form>

</body>

