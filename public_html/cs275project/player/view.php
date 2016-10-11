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
if($id == 'last'){
	$query = "SELECT * FROM Player ORDER BY playerId DESC LIMIT 0, 1";
} else {
	$query = "SELECT * FROM Player WHERE playerId = $id";
}

$result = mysqli_query($dbc, $query) or die("Could not select player" . $query);
$player = mysqli_fetch_assoc($result);

?>
<a href="../main.php">Homepage</a><br>
<a href="index.php">Back to Players</a><br>
<title><?= $player['lastName'] . ", " . $player['firstName'] ?></title>
<h1><?= $player['firstName'] . ' ' . $player['lastName'] ?></h1>
<h3>Born <?= $player['dob'] ?></h3>

<?php
if($player['teamId'] == 0){
	echo "Currently a free agent";
} else {
	$query = "SELECT * FROM Team where teamId = ${player['teamId']}";
	$result = mysqli_query($dbc, $query);
	$team = mysqli_fetch_assoc($result);
	echo "Currently playing for ${team['name']}";
}

?>

<?php
$query = "SELECT * FROM Position as p, PlayerPosition as pp WHERE pp.playerId = $id AND pp.positionId = p.positionId ";
$result = mysqli_query($dbc, $query) or die("Could not select positions " . $query);

$positions = "<p><b>Positions:</b> ";

while($position = mysqli_fetch_assoc($result)){
	$positions .= $position['name'];
	$positions .= ', ';
}

$positions = substr($positions, 0, -2);
$positions .= '</p>';
echo $positions;
?>

<a href="edit.php?id=<?= $player['playerId'] ?>">Edit Player</a>


