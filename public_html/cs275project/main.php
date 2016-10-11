<?php
session_start();
if($_SESSION['id'] != 'password'){
	header("Location: index");
}
?>

<title>Welcome!</title>
<h2>Homepage</h2>
<a href="team">View Teams</a><br>
<a href="player">View Players</a><br>
<a href="match">View Matches</a><br>
<a href="season">View Seasons</a><br>
<a href="stadium">View Stadiums</a>