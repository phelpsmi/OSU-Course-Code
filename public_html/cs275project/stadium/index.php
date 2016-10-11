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

<table>
	<tr>
		<th>ID</th>
		<th>Team</th>
		<th>State</th>
		<th>City</th>
		<th>Address</th>
		<th>Capacity</th>
		<th>Surface</th>
		<th>Open Roof</th>
		<th></th>
	</tr>
<?php

$query = "SELECT * FROM Stadium ";
$result = mysqli_query($dbc, $query)
	or die("Error fetching teams");

while($row = mysqli_fetch_assoc($result)){
	$team = "";
	$query = "SELECT * FROM Team WHERE teamId = ${row['teamId']}";
	$team = mysqli_query($dbc, $query);
	$team = mysqli_fetch_assoc($team);
	
	if($row['openRoof'])
		$openRoof = "Yes";
	else
		$openRoof = "No";
	echo "<tr>";
	echo "<td>" . $row['stadiumId'] . "</td>";
	echo "<td>" . $team['name'] . "</td>";
	echo "<td>" . $row['state'] . "</td>";
	echo "<td>" . $row['city'] . "</td>";
	echo "<td>" . $row['address'] . "</td>";
	echo "<td>" . $row['capacity'] . "</td>";
	echo "<td>" . $row['surface'] . "</td>";
	echo "<td>" . $openRoof . "</td>";
	echo "<td><a href='../team/edit?id=${row['teamId']}'>Edit</a></td>";
	echo "</tr>";
}




?>