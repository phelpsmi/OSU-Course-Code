<?php
$dbhost = 'oniddb.cws.oregonstate.edu';
$dbname = 'phelpsmi-db';
$dbuser = 'phelpsmi-db';
$dbpass = 'kPMlMYXHsXV0VOML';

$dbc = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname)
    or die("Error connecting to database server");

if($_POST['formSubmit'] == "Submit") {
    
    $s_id = $_POST['s_id'];
    $first_name = $_POST['first_name'];
    $last_name = $_POST['last_name'];
    $email_address = $_POST['email_address'];
    $age = $_POST['age'];
    $gender = $_POST['gender'];
    $major = $_POST['major'];
    $courses = $_POST['courses'];
    $_GET['s_id'] = $s_id;

    $error = false;
    $errors = array();
    if(!filter_var($email_address, FILTER_VALIDATE_EMAIL)){
        $error = true;
        $errors[] = "Must enter a valid email";
    }
    if(!filter_var($age, FILTER_VALIDATE_INT)){
        $error = true;
        $errors[] = "Age must be a number";
    }
    if(!filter_var($s_id, FILTER_VALIDATE_INT)){
        $error = true;
        $errors[] = "ID must be a number";
    }

    $query = "SELECT s_id FROM Student WHERE s_id = '" . $s_id . "'";
    $result = mysqli_query($query);
    if(mysqli_num_rows($result) != 0){
        $error = true;
        $errors[] = "ID must be unique";
    }

    if($error){
        $message = 'The following errors occured in your form: \n';
        foreach ($errors as $e){
            $message .= $e;
            $message .= '\n';
        }
        echo "<SCRIPT> alert('$message'); </SCRIPT>";
        echo "<a href='form.php'><h3>Go back to Form</h3></a>";
        echo "<a href='student_index.php'><h3>View student index</h3></a>";
    }
    else{
        $query = "INSERT INTO Student (s_id, first_name, last_name, email_address, age, gender, major)
              "."VALUES ('$s_id', '$first_name', '$last_name', '$email_address', '$age', '$gender', '$major')";
        $result = mysqli_query($dbc, $query) or die("Error querrying database! " . $query);

        foreach ($courses as $c){
            $query = "INSERT INTO Enrollment (s_id, c_id) VALUES ('$s_id', '$c')";
            $result = mysqli_query($dbc, $query) or die("Error querrying database!" . $query);
        }
        $message = 'Thank you ' . $first_name . ". We have successfully recorded your student information";

        echo "<SCRIPT> alert('$message'); </SCRIPT>";
        echo "<a href='student_view.php?s_id=" . $s_id . "'><h3>View your page</h3></a>";
        echo "<a href='student_index.php'><h3>View student index</h3></a>";
    }
}

?>