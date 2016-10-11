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

	$season = $_POST['season'];
	$homeId = $_POST['homeId'];
	$awayId = $_POST['awayId'];
	$date = $_POST['date'];
	$hour = $_POST['hour'];
	$minute = $_POST['minute'];
	$homeWin = $_POST['homeWin'];

	$errors = array();
	if(empty($season)){
		$errors[] = "Season missing";
	}
	if(empty($homeId)){
		$errors[] = "Home team missing";
	}
	if(empty($awayId)){
		$errors[] = "Away team missing";
	} else if($awayId == $homeId){
		$errors[] = "A team can't play itself";
	}
	if(empty($homeWin)){
		$errors[] = "Must select a winner";
	}
	if(empty($date)){
		$errors[] = "Date missing";
	} else if(!preg_match("/^[0-9]{4}-[0-9]{2}-[0-9]{2}$/", $date)){
		$errors[] = "Date not in proper date format";
	}
	if(empty($hour)){
		$errors[] = "Must select the hour the game started";
	}
	if(empty($minute)){
		$errors[] = "Must select the minute the game started";
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

		if(intval($hour) < 10)
			$hour = '0' . $hour;
		if(intval($minute) < 10)
			$minute = '0' . $minute;
		$date .= ':' . $hour . ':' . $minute . ':00';

		$query = "INSERT INTO `Match` (seasonYear, homeId, awayId, `date`, homeWin ) ";
		$query .= "VALUES ($season, $homeId, $awayId, '$date', $homeWin)";
		$result = mysqli_query($dbc, $query) or die("Error querrying database $query");
	}

}

?>

<head>
<title>New Team</title>
</head>

<body>

<a href="../main.php">Homepage</a><br>
<a href="index.php">Back to Index</a><br><br>

<form action="<?= htmlspecialchars($_SERVER['PHP_SELF']) ?>" method="POST">

Season: 
<select name='season'>
<option value=''></option>
<?php
$query = "SELECT * FROM Season";
$result = mysqli_query($dbc, $query) or die("Error fetching seasons");
while($season = mysqli_fetch_assoc($result)){
	echo "<option value='${season['year']}'>${season['year']}</option>";
}
?>
</select><br>


Date: <input type="text" name="date" placeholder="YYYY-MM-DD"><br>

Hour
<select name="hour">
	<option value=''></option>
    <?php for ($i = 1; $i <= 24; $i++) : ?>
        <option value="<?php echo $i; ?>"><?php echo $i; ?></option>
    <?php endfor; ?>
</select>
Minute:
<select name="minute">
	<option value=''></option>
    <?php for ($i = 0; $i <= 59; $i++) : ?>
        <option value="<?php echo $i; ?>"><?php echo $i; ?></option>
    <?php endfor; ?>
</select>
<br>


Home Team:
<select name='homeId'>
<option value=''></option>
<?php
$query = "SELECT * FROM Team";
$result = mysqli_query($dbc, $query) or die("Error fetching teams");
while($team = mysqli_fetch_assoc($result)){
	echo "<option value='${team['teamId']}'>${team['name']}</option>";
}
?>
</select>
Winner:<input type="radio" name="homeWin" value='1'>
<br>


Away Team: 
<select name='awayId'>
<option value=''></option>
<?php
$query = "SELECT * FROM Team";
$result = mysqli_query($dbc, $query) or die("Error fetching teams");
while($team = mysqli_fetch_assoc($result)){
	echo "<option value='${team['teamId']}'>${team['name']}</option>";
}
?>
</select>
Winner:<input type="radio" name="homeWin" value='0'>
<br><br>


<input type="submit" name="formSubmit" value="Search">

</form>

</body>