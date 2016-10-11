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

if($_GET['formSubmit'] == "Search"){
	$season = $_GET['season'];
	$homeId = $_GET['homeId'];
	$awayId = $_GET['awayId'];
	$date = $_GET['date'];

	$search = "WHERE 1";
	if(!empty($season)){
		$search .= " AND seasonYear = $season";
	}
	if(!empty($homeId)){
		$search .= " AND homeId = $homeId";
	}
	if(!empty($awayId)){
		$search .= " AND awayId = $awayId";
	}
	if(!empty($date)){
		$search .= " AND DATE(`date`) = '$date'";
	}
}
?>

<a href="../main.php">Homepage</a><br>
<a href="new.php">Enter a new match</a><br><br>

<form action="<?= htmlspecialchars($_SERVER["PHP_SELF"]) ?>" method="GET">

Search:<br>

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
</select><br>

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
</select><br>

Date Played: <input type="text" name="date" placeholder="YYYY-MM-DD"><br>


<input type="submit" name="formSubmit" value="Search">


</form>


<table>
	<tr>
		<th>ID</th>
		<th>Season</th>
		<th>Home Team</th>
		<th>Away Team</th>
		<th>Winner</th>
		<th>Date Played</th>
		<th></th>
		<th></th>
	</tr>
<?php

$query = "SELECT * FROM `Match` $search";
$result = mysqli_query($dbc, $query)
	or die("Error fetching matches $query");

while($row = mysqli_fetch_assoc($result)){

	$query = "SELECT * FROM Team WHERE teamId = ${row['homeId']}";
	$teamResult = mysqli_query($dbc, $query) or die("error getting team $query");
	$homeTeam = mysqli_fetch_assoc($teamResult);

	$query = "SELECT * FROM Team WHERE teamId = ${row['awayId']}";
	$teamResult = mysqli_query($dbc, $query) or die("error getting team $query");
	$awayTeam = mysqli_fetch_assoc($teamResult);

	echo "<tr>";
	echo "<td>" . $row['matchId'] . "</td>";
	echo "<td>" . $row['seasonYear'] . "</td>";
	echo "<td>" . $homeTeam['name'] . "</td>";
	echo "<td>" . $awayTeam['name'] . "</td>";
	if($row['homeWin']){
		echo "<td>${homeTeam['name']}</td>";
	} else {
		echo "<td>${awayTeam['name']}</td>";
	}
	echo "<td>" . $row['date'] . "</td>";
	echo "<td><a href='edit.php?id=" . $row['matchId'] . "'>Edit</a></td>";
	echo "</tr>";

}

?>