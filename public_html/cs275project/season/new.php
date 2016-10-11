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

if($_POST['formSubmit'] == "Submit") {

    $year = $_POST['year'];
    $teams = $_POST['team'];

//error checking on all the inputs
    $errors = array();
    if(empty($year)){
    	$errors[] = "Year missing";
    } else if(!filter_var($year, FILTER_VALIDATE_INT)){
        $errors[] = "Year must be a number";
    } else if(strlen($year) != 4){
        $errors[] = "Year must be 4 digits";
    } else {
        $query = "SELECT * FROM Season WHERE year = $year";
        $result = mysqli_query($dbc, $query);
        if(mysqli_fetch_assoc($result)){
            $errors[] = "Season already registered";
        }
    }
    if(empty($teams)){
        $errors[] = "Must select atleast one team";
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
        $query = "INSERT INTO Season (year) VALUES ($year)";
        $result = mysqli_query($dbc, $query) or die("Error querrying database! " . $query);


        foreach($teams as $teamId){
            $query = "INSERT INTO SeasonTeam (year, teamId) ";
            $query .= "VALUES ('$year', $teamId)";
            $result = mysqli_query($dbc, $query) or die("Error inserting teams $query");
        }


        //echo "<SCRIPT> alert('$message'); </SCRIPT>";
        header("Location: view?id=$year");
		exit(); 
    }
}

?>

<a href="../main.php">Homepage</a><br>
<a href="index.php">Team Index</a><br><br>

<h2>New Season</h2>

<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>" method="POST">

Year:<input type="text" name="year" value=""><br>

<?php

$i = 0;

$query = "SELECT * FROM Team";
$result = mysqli_query($dbc, $query) or die("Error fetching teams $query");
while($team = mysqli_fetch_assoc($result)){ 
    echo "&nbsp;&nbsp;&nbsp;";
    echo "<input type='checkbox' name='team[$i]' value='${team['teamId']}'>";
    echo "${team['name']} ";
    echo "<br>";
    $i++;


}

?>

<input type="submit" name="formSubmit" value="Submit">

</form>