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
<a href="new.php">Start a new season</a><br><br>


<table>
	<tr>
		<th>Year</th>
		<th>Winner</th>
		<th></th>
		<th></th>
	</tr>
<?php

$query = "SELECT * FROM Season ORDER BY year ASC";
$result = mysqli_query($dbc, $query)
	or die("Error fetching teams");

while($row = mysqli_fetch_assoc($result)){
	$winner['name'] = "TBA";
	if(!empty($row['winnerId'])){
		$query = "SELECT * FROM Team WHERE teamId = ${row['winnerId']}";
		$winner = mysqli_query($dbc, $query);
		$winner = mysqli_fetch_assoc($winner);
	}
	echo "<tr>";
	echo "<td>" . $row['year'] . "</td>";
	echo "<td>" . $winner['name'] . "</td>";
	echo "<td><a href='view.php?id=" . $row['year'] . "'>View</a></td>";
	echo "<td><a href='edit.php?id=" . $row['year'] . "'>Edit</a></td>";
	echo "</tr>";

}



?>