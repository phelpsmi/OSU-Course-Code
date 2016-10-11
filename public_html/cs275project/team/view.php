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
	$query = "SELECT * FROM Team ORDER BY teamId DESC LIMIT 0, 1";
} else {
	$query = "SELECT * FROM Team WHERE teamId = $id";
}

$result = mysqli_query($dbc, $query) or die("Could not select team" . $query);
$team = mysqli_fetch_assoc($result);

?>
<a href="../main.php">Homepage</a><br>
<a href="index.php">Back to Teams</a><br>
<title><?= $team['name'] ?></title>
<h1><?= $team['name'] ?></h1>
<h3><?= $team['city'] ?></h3>
<h3><?= $team['sponsor'] ?></h3>

<?php
$query = "SELECT * FROM Player WHERE teamId = " . $team['teamId'];
$result = mysqli_query($dbc, $query) or die("Could not select players " . $query);
?>

<table>
	<tr>
		<th>Player ID</th>
		<th>First Name</th>
		<th>Last Name</th>
		<th></th>
	</tr>

<?php
while($player = mysqli_fetch_assoc($result)){
?>

	<tr>
		<td><?= $player['playerId'] ?></td>
		<td><?= $player['firstName'] ?></td>
		<td><?= $player['lastName'] ?></td>
		<th><a href="../player/view.php?id=<?= $player['playerId'] ?>">View</a></th>
	</tr>
<?php } ?>
</table>

<a href="edit.php?id=<?= $team['teamId'] ?>">Edit Team</a>


