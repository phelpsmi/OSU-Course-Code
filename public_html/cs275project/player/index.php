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
?>

<a href="../main.php">Homepage</a><br>
<a href="new.php">Register a new Player</a><br><br>

<form action="<?= htmlspecialchars($_SERVER["PHP_SELF"]) ?>" method="GET">

Search:<br>

Team:
<select name='teamId'>
<option value=''></option>
<?php
$query = "SELECT * FROM Team";
$result = mysqli_query($dbc, $query) or die("Error fetching teams");
while($team = mysqli_fetch_assoc($result)){
	$selected = "";
	if($_GET['teamId'] == $team['teamId'])
		$selected = "selected";
	echo "<option value='${team['teamId']}' ${selected}>${team['name']}</option>";
}
?>
</select><br>

Position:
<select name='position'>
<option value=''></option>
<?php
$query = "SELECT * FROM Position";
$result = mysqli_query($dbc, $query) or die("Error fetching positions $query");
while($pos = mysqli_fetch_assoc($result)){
	$selected = "";
	if($_GET['position'] == $pos['positionId'])
		$selected = "selected";
	echo "<option value='${pos['positionId']}' ${selected}>${pos['name']}</option>";
}
?>
</select><br>

<input type="submit" name="formSubmit" value="Search">
<input type="submit" value="Reset">

</form>


<table>
	<tr>
		<th>ID</th>
		<th>First Name</th>
		<th>Last Name</th>
		<th>Born</th>
		<th>Team</th>
		<th></th>
		<th></th>
	</tr>
<?php

if($_GET['formSubmit'] == "Search"){
	$teamId = $_GET['teamId'];
	$positionId = $_GET['position'];

	$search = "";
	if(!empty($teamId)){
		$search .= " AND Player.teamId = $teamId";
	}
	if(!empty($positionId)){
		$query = "SELECT * from Player, PlayerPosition as pp
				  where Player.playerId = pp.playerId AND pp.positionId = '$positionId'
				  $search";
	} else {
		$query = "SELECT * FROM Player WHERE 1 $search";
	}
} else {
	$query = "SELECT * FROM Player";
}

$result = mysqli_query($dbc, $query)
	or die("Error fetching players");

while($row = mysqli_fetch_assoc($result)){

	if($row['teamId'] == 0){
		$team = "FREE AGENT";
	} else {
		$teamId = $row['teamId'];
		$query = "SELECT * FROM Team WHERE teamId = $teamId";
		$team = mysqli_query($dbc, $query)
			or die("Error fetching team $query");
		$team = mysqli_fetch_assoc($team)
			or die("$query");
		$team = $team['name'];
	}

	echo "<tr>";
	echo "<td>" . $row['playerId'] . "</td>";
	echo "<td>" . $row['firstName'] . "</td>";
	echo "<td>" . $row['lastName'] . "</td>";
	echo "<td>" . $row['dob'] . "</td>";
	echo "<td>" . $team . "</td>";
	echo "<td><a href='view.php?id=" . $row['playerId'] . "'>View</a></td>";
	echo "<td><a href='edit.php?id=" . $row['playerId'] . "'>Edit</a></td>";
	echo "</tr>";

}



?>