<?php

$dbhost = 'oniddb.cws.oregonstate.edu';
$dbname = 'phelpsmi-db';
$dbuser = 'phelpsmi-db';
$dbpass = 'kPMlMYXHsXV0VOML';

$dbc = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname)
    or die("Error connecting to database server");

$sID = $_GET['sID'];
$query = "SELECT * FROM Student_T WHERE sID = $sID";
$result = mysqli_query($dbc, $query) or die($query);
$student = mysqli_fetch_assoc($result);

$firstName = $_POST['firstName'] or $firstName = $student['firstName'];
$lastName = $_POST['lastName'] or $lastName = $student['lastName'];
$email = $_POST['email'] or $email = $student['email'];
$bDate = $_POST['bDate'] or $bDate = $student['bDate'];
$major = $_POST['majorj'] or $major = $student['major'];

if($_POST['formSubmit'] == "Submit"){
    //error checking on all the inputs
    $errors = array();
    if(empty($email)){
    	$errors[] = "Email missing";
    }
    elseif(!filter_var($email, FILTER_VALIDATE_EMAIL)){
        $errors[] = "Must enter a valid email";
    }
    if(empty($bDate)){
    	$errors[] = 'Age missing';
    }
    elseif(!preg_match( "/^[0-9]{4}-[0-9]{2}-[0-9]{2}$/", $bDate)) {
        $errors[] = "Birthdate must be in format YYYY-MM-DD";
    }
    

    if($errors){
        $message = 'The following errors occured in your form: \n';
        foreach ($errors as $e){
            $message .= $e;
            $message .= '\n';
        }
        echo "<SCRIPT> alert('$message'); </SCRIPT>";
    } else {
    	$query = "UPDATE Student_T SET firstName = '$firstName', lastName = '$lastName', bDate = '$bDate'
                 "."WHERE sID = $sID";
        $result = mysqli_query($dbc, $query) or die("Error querrying database! " . $query);

        $message = 'Thank you ' . $firstName . ". We have successfully updated your student information";

        //echo "<SCRIPT> alert('$message'); </SCRIPT>";
        header("Location: student_view?sID=" . $sID . "&message=" . urlencode($message));
		exit(); 
    }
}

?>
<!DOCTYPE html


<html>

<head>
<title>New Student</title>
</head>

<body>

<p>Welcome student, please enter your information</p>
<!-- PHP code here allows me to retain values after a failed submission -->

<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]) . "?sID=$sID";?>" method="POST">
Student ID: <input type="text" name="sID" value="<?php echo $sID; ?>" readonly ><br>
First Name: <input type="text" name="firstName" value="<?php echo $firstName; ?>"><br>
Last Name: <input type="text" name="lastName" value="<?php echo $lastName; ?>"><br>
E-mail: <input type="text" name="email" value="<?php echo $email; ?>"><br>
Birthdate: <input type="text" name="bDate" value="<?php echo $bDate; ?>"><br>

Major: <br />
<input type="radio" name="major" value="CS" <?php if($major == 'CS') echo "checked" ?> >CS<br />
<input type="radio" name="major" value="EE" <?php if($major == 'EE') echo "checked" ?> >EE<br />
<input type="radio" name="major" value="other" <?php if($major == 'other') echo "checked" ?> >Other<br />


<input type="submit" name="formSubmit" value="Submit">
</form>

<a href="student_view.php?sID= <?php echo $sID; ?>">Return to student</a>

</body>
</html>