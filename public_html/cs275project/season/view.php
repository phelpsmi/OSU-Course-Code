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
$query = "SELECT * FROM Season WHERE year = $id";
$result = mysqli_query($dbc, $query) or die("Could not select season" . $query);
$season = mysqli_fetch_assoc($result);

?>
<a href="../main.php">Homepage</a><br>
<a href="index.php">Back to Seasons</a><br>
<title><?= "$id Season" ?></title>
<h1><?= "The $id NFL Season" ?></h1>

<table>
	<tr>
		<th>Team</th>
		<th>Wins</th>
		<th>Loss</th>
	</tr>

<?php
$query = "SELECT * FROM Team as t, SeasonTeam as st 
		  WHERE t.teamId = st.teamId AND st.year = $id";
$result = mysqli_query($dbc, $query) or die("Could not select teams $query");

while($team = mysqli_fetch_assoc($result)){
	$wins = 0;
	$loss = 0;
	$query = "SELECT * FROM `Match` WHERE homeId = ${team['teamId']} AND seasonYear = $id";
	$matches = mysqli_query($dbc, $query) or die("Could not select home games $query");
	while($match = mysqli_fetch_assoc($matches)){
		if($match['homeWin'])
			$wins++;
		else
			$loss++;
	}
	$query = "SELECT * FROM `Match` WHERE awayId = ${team['teamId']} AND seasonYear = $id";
	$matches = mysqli_query($dbc, $query) or die("Could not select away games $query");
	while($match = mysqli_fetch_assoc($matches)){
		if($match['homeWin'])
			$loss++;
		else
			$wins++;
	}
	echo "<tr>";
	echo "<td>${team['name']}</td>";
	echo "<td>$wins</td>";
	echo "<td>$loss</td>";
	echo "</tr>";

}
?>

</table>

<a href="edit.php?id=<?= $id ?>">Edit Season</a>
