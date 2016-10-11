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

$id = $_GET['id'];


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
	if(empty($homeWin) && $homeWin != '0'){
		$errors[] = "Must select a winner";
	}
	if(empty($date)){
		$errors[] = "Date missing";
	} else if(!preg_match("/^[0-9]{4}-[0-9]{2}-[0-9]{2}$/", $date)){
		$errors[] = "Date not in proper date format";
	}
	if(empty($hour) && $hour != '0'){
		$errors[] = "Must select the hour the game started";
	}
	if(empty($minute) && $minute != '0'){
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

		$query = "UPDATE `Match` 
				  SET seasonYear = $season, homeId = $homeId, awayId = $awayId, `date` = '${date}', homeWin = $homeWin
				  WHERE matchId = $id";
		$result = mysqli_query($dbc, $query) or die("Error querrying database $query");
	}

}

$query = "SELECT * FROM `Match` WHERE matchId = $id";
$result = mysqli_query($dbc, $query) or die("could not select match $query");
$match = mysqli_fetch_assoc($result);
$date = strtotime($match['date']);

?>

<head>
<title>New Team</title>
</head>

<body>

<a href="../main.php">Homepage</a><br>
<a href="index.php">Back to Index</a><br><br>

<form action="<?= htmlspecialchars($_SERVER['PHP_SELF']) . "?id=$id" ?>" method="POST">

Season: 
<select name='season'>
<option value=''></option>
<?php
$query = "SELECT * FROM Season";
$result = mysqli_query($dbc, $query) or die("Error fetching seasons");
while($season = mysqli_fetch_assoc($result)){
	$selected = '';
	if ($match['seasonYear'] == $season['year'])
		$selected = "selected='selected'";
	echo "<option value='${season['year']}' ${selected}>${season['year']}</option>";
}
?>
</select><br>


Date: <input type="text" name="date" placeholder="YYYY-MM-DD" value="<?= substr($match['date'], 0, 10) ?>"><br>

Hour: 
<select name="hour">
	<option value=''></option>
    <?php for ($i = 0; $i <= 23; $i++) : ?>
    	<?php 
    	$selected = '';
		if (intval(date('H', $date)) == $i)
			$selected = "selected='selected'";
		?>
        <option value="<?php echo $i; ?>" <?= $selected ?> ><?php echo $i; ?></option>
    <?php endfor; ?>
</select>
Minute:
<select name="minute">
	<option value=''></option>
    <?php for ($i = 0; $i <= 59; $i++) : ?>
    	<?php 
    	$selected = '';
		if (intval(date('i', $date)) == $i)
			$selected = "selected='selected'";
		?>
        <option value="<?php echo $i; ?>" <?= $selected ?> ><?php echo $i; ?></option>
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
	$selected = '';
	if ($team['teamId'] == $match['homeId'])
		$selected = "selected='selected'";
	echo "<option value='${team['teamId']}' ${selected}>${team['name']}</option>";
}
?>
</select>
<?php if($match['homeWin'] == 1): ?>
Winner:<input type="radio" name="homeWin" value='1' checked>
<?php else: ?>
Winner:<input type="radio" name="homeWin" value='1'>
<?php endif; ?>
<br>


Away Team: 
<select name='awayId'>
<option value=''></option>
<?php
$query = "SELECT * FROM Team";
$result = mysqli_query($dbc, $query) or die("Error fetching teams");
while($team = mysqli_fetch_assoc($result)){
	$selected = '';
	if ($team['teamId'] == $match['awayId'])
		$selected = "selected='selected'";
	echo "<option value='${team['teamId']}' ${selected}>${team['name']}</option>";
}
?>
</select>
<?php if($match['homeWin'] == 0): ?>
Winner:<input type="radio" name="homeWin" value='0' checked>
<?php else: ?>
Winner:<input type="radio" name="homeWin" value='0'>
<?php endif; ?>
<br><br>


<input type="submit" name="formSubmit" value="Submit">

</form>

</body>