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


if($_POST['formSubmit'] == "Submit") {

    $name = $_POST['name'];
    $city = $_POST['city'];
    $sponsor = $_POST['sponsor'];
    $state = $_POST['state'];
    $city = $_POST['city'];
    $address = $_POST['address'];
    $capacity = $_POST['capacity'];
    $surface = $_POST['surface'];
    $openRoof = $_POST['openRoof'];


//error checking on all the inputs
    $errors = array();
    if(empty($name)){
    	$errors[] = "City missing";
    }
    if(empty($city)){
    	$errors[] = 'City missing';
    }
    if(empty($sponsor)){
    	$errors[] = "Sponsor missing";
    }
    if(empty($state)){
        $errors[] = "Stadium state missing";
    }
    if(empty($city)){
        $errors[] = "Stadium city missing";
    }
    if(empty($address)){
        $errors[] = "Stadium address missing";
    }
    if(empty($capacity)){
        $errors[] = "Stadium capacity missing";
    } elseif(!filter_var($capacity, FILTER_VALIDATE_INT)) {
        $errors[] = "Stadium capacity must be a number";
    }
    if(empty($openRoof)){
        $openRoof = '0';
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
        $query = "UPDATE Team SET name = '$name', city = '$city', sponsor = '$sponsor'
        		 "." WHERE teamId = $id";
        $result = mysqli_query($dbc, $query) or die("Error querrying database! " . $query);

        $query = "UPDATE Stadium SET state = '$state', city = '$city', address = '$address', 
                                    capacity = $capacity, surface = '$surface', openRoof = $openRoof
                    WHERE teamId = $id";
        $result = mysqli_query($dbc, $query) or die("Error updating stadium $query");

        header("Location: view?id=$id" . urlencode($message));
		exit(); 
    }
}

$query = "SELECT * FROM Team WHERE teamId = $id";
$result = mysqli_query($dbc, $query) or die("Could not select team");
$team = mysqli_fetch_assoc($result);

$query = "SELECT * FROM Stadium WHERE teamId = $id";
$result = mysqli_query($dbc, $query) or die("Could not select stadium $query");
$stadium = mysqli_fetch_assoc($result);

?>

<a href="../main.php">Homepage</a><br>
<a href="index.php">Back to Teams</a><br><br>

<form action="<?= htmlspecialchars($_SERVER["PHP_SELF"]) . '?id=' . $id ?>" method="POST">

Name:    <input type="text" name="name" value="<?= $team['name'] ?>"><br>
City:    <input type="text" name="city" value="<?= $team['city'] ?>"><br>
Sponsor: <input type="text" name="sponsor" value="<?= $team['sponsor'] ?>"><br><br>

<b>Stadium Info:</b><br>
State: <input type="text" name="state" value="<?= $stadium['state'] ?>"><br>
City: <input type="text" name="city" value="<?= $stadium['city'] ?>"><br>
Address: <input type="text" name="address" value="<?= $stadium['address'] ?>"><br>
Capacity: <input type="text" name="capacity" value="<?= $stadium['capacity'] ?>"><br>
Surface: <input type="text" name="surface" value="<?= $stadium['surface'] ?>"><br>
<?php if($stadium['openRoof'] == '1'): ?>
Open Roof: <input type="checkbox" name="openRoof" value='1' checked><br>
<?php else: ?>
Open Roof: <input type="checkbox" name="openRoof" value='1'><br>
<?php endif ?>

<input type="submit" name="formSubmit" value="Submit">

</form>