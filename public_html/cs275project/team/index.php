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
<a href="new.php">Register a new team</a><br><br>


<table>
	<tr>
		<th>ID</th>
		<th>Name</th>
		<th>City</th>
		<th>Sponsor</th>
		<th></th>
		<th></th>
	</tr>
<?php

$query = "SELECT * FROM Team";
$result = mysqli_query($dbc, $query)
	or die("Error fetching teams");

while($row = mysqli_fetch_assoc($result)){
	echo "<tr>";
	echo "<td>" . $row['teamId'] . "</td>";
	echo "<td>" . $row['name'] . "</td>";
	echo "<td>" . $row['city'] . "</td>";
	echo "<td>" . $row['sponsor'] . "</td>";
	echo "<td><a href='view.php?id=" . $row['teamId'] . "'>View</a></td>";
	echo "<td><a href='edit.php?id=" . $row['teamId'] . "'>Edit</a></td>";
	echo "</tr>";

}



?>