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
$result = mysqli_query($dbc, $query);
$season = mysqli_fetch_assoc($result);

if($_POST['formSubmit'] == "Submit") {

    $year = $_POST['year'];
    $teams = $_POST['team'];
    $winnerId = $_POST['winnerId'];

//error checking on all the inputs
    $errors = array();
    if(empty($year)){
    	$errors[] = "Year missing";
    } else if(!filter_var($year, FILTER_VALIDATE_INT)){
        $errors[] = "Year must be a number";
    } else if(strlen($year) != 4){
        $errors[] = "Year must be 4 digits";
    } else {
        if($year != $id){
            $query = "SELECT * FROM Season WHERE year = $year";
            $result = mysqli_query($dbc, $query);
            if(mysqli_fetch_assoc($result)){
                $errors[] = "Season already registered";
            }
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
        if(empty($winnerId))
            $query = "UPDATE Season SET year = $year WHERE year = $id";
        else
            $query = "UPDATE Season SET year = $year, winnerId = $winnerId WHERE year = $id";
        $result = mysqli_query($dbc, $query) or die("Error querrying database! " . $query);

        $query = "DELETE FROM SeasonTeam WHERE year = $id";
        $result = mysqli_query($dbc, $query) or die("Error deleting teams $query");

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

<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]) . "?id=" . $id;?>" method="POST">

Year:<input type="text" name="year" value="<?= $id ?>"><br>

<?php

$i = 0;

$query = "SELECT * FROM Team";
$result = mysqli_query($dbc, $query) or die("Error fetching teams $query");
while($team = mysqli_fetch_assoc($result)){
    $checked = "";
    $query = "SELECT * FROM SeasonTeam WHERE teamId = ${team['teamId']} AND year = $id";
    if(mysqli_fetch_assoc(mysqli_query($dbc, $query))){
        $checked = "checked";
    }
    echo "&nbsp;&nbsp;&nbsp;";
    echo "<input type='checkbox' name='team[$i]' value='${team['teamId']}' ${checked}>";
    echo "${team['name']} ";
    echo "<br>";
    $i++;
}
?>
<br>

Winner: <SELECT name='winnerId'>
<option value=''></option>
<?php
$query = "SELECT * FROM Team as t, SeasonTeam as st WHERE t.teamId = st.teamId AND st.year = $id";
$result = mysqli_query($dbc, $query) or die("Error fetching teams $query");
while($team = mysqli_fetch_assoc($result)){
    $selected = "";
    if($season['winnerId'] == $team['teamId'])
        $selected = "selected";
    echo "<option value='${team['teamId']}' $selected>${team['name']}</option>";
}
?>
</SELECT><br><br>

<input type="submit" name="formSubmit" value="Submit">

</form>