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
        $query = "INSERT INTO Team (name, city, sponsor)
              "."VALUES ('$name', '$city', '$sponsor')";
        $result = mysqli_query($dbc, $query) or die("Error querrying database! " . $query);

        $query = "SELECT * FROM Team ORDER BY teamId DESC LIMIT 1";
        $result = mysqli_query($dbc, $query);
        $team = mysqli_fetch_assoc($result);

        $query = "INSERT INTO Stadium (state, city, address, capacity, teamId, surface, openRoof)
                  VALUES ('$state', '$city', '$address', $capacity, ${team['teamId']}, '$surface', $openRoof)";
        $result = mysqli_query($dbc, $query) or die("Error creating stadium $query");

        //echo "<SCRIPT> alert('$message'); </SCRIPT>";
        header("Location: view?id=${team['teamId']}" . urlencode($message));
		exit(); 
    }
}

?>

<a href="../main.php">Homepage</a><br>
<a href="index.php">Team Index</a><br><br>

<h2>New Team</h2>

<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>" method="POST">

Name:    <input type="text" name="name" value=""><br>
City:    <input type="text" name="city" value=""><br>
Sponsor: <input type="text" name="sponsor" value=""><br><br>

<b>Stadium Info:</b><br>
State: <input type="text" name="state" value=""><br>
City: <input type="text" name="city" value=""><br>
Address: <input type="text" name="address" value=""><br>
Capacity: <input type="text" name="capacity" value=""><br>
Surface: <input type="text" name="surface" value=""><br>
Open Roof: <input type="checkbox" value='1'><br>

<input type="submit" name="formSubmit" value="Submit">

</form>