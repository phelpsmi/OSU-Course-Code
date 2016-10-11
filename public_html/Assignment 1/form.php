<?php 
$dbhost = 'oniddb.cws.oregonstate.edu';
$dbname = 'phelpsmi-db';
$dbuser = 'phelpsmi-db';
$dbpass = 'kPMlMYXHsXV0VOML';

$dbc = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname)
    or die("Error connecting to database server");

if($_POST['formSubmit'] == "Submit") {
    
    $sID = $_POST['sID'];
    $firstName = $_POST['firstName'];
    $lastName = $_POST['lastName'];
    $email = $_POST['email'];
    $bDate = $_POST['bDate'];
    $gender = $_POST['gender'];
    $major = $_POST['major'];
    $courses = $_POST['courses'];


//error checking on all the inputs
    $errors = array();
    if(empty($email)){
    	$errors[] = "Email missing";
    }
    elseif(!filter_var($email, FILTER_VALIDATE_EMAIL)){
        $errors[] = "Must enter a valid email";
    }
    if(empty($bDate)){
    	$errors[] = 'Birthdate missing';
    }
    elseif(!preg_match( "/^[0-9]{4}-[0-9]{2}-[0-9]{2}$/", $bDate)){
        $errors[] = "Birthdate must be in format YYYY-MM-DD";
    }
    if(empty($_POST['major'])){
    	$errors[] = "Major missing";
    }
    if(empty($sID)){
        $errors[] = 'Student ID missing';
    }
    elseif(!filter_var($sID, FILTER_VALIDATE_INT)){
        $errors[] = "ID must be a number";
    } else {
        $query = "SELECT * FROM Student_T WHERE sID = $sID";
        $result = mysqli_query($dbc, $query) or die("myql error: $query");
        if(mysqli_fetch_assoc($result)){
            $errors[] = "ID must be unique";
        } 
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
        $query = "INSERT INTO Student_T (sID, firstName, lastName, email, bDate, major)
              "."VALUES ('$sID', '$firstName', '$lastName', '$email', '$bDate', '$major')";
        $result = mysqli_query($dbc, $query) or die("Error querrying database! " . $query);

        foreach ($courses as $cID){
            $query = "INSERT INTO Enrollment_T (sID, cID) VALUES ('$sID', '$cID')";
            $result = mysqli_query($dbc, $query) or die("Error querrying database!" . $query);
        }
        $message = 'Thank you ' . $firstName . ". We have successfully recorded your student information";

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

<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>" method="POST">
Student ID: <input type="text" name="sID" value="<?php if(isset($_POST['sID'])){ echo $_POST['sID']; } ?>"><br>
First Name: <input type="text" name="firstName" value="<?php if(isset($_POST['firstName'])){ echo $_POST['firstName']; } ?>"><br>
Last Name: <input type="text" name="lastName" value="<?php if(isset($_POST['lastName'])){ echo $_POST['lastName']; } ?>"><br>
E-mail: <input type="text" name="email" value="<?php if(isset($_POST['email'])){ echo $_POST['email']; } ?>"><br>
Birthdate(YYYY-MM-DD): <input type="text" name="bDate" value="<?php if(isset($_POST['bDate'])){ echo $_POST['bDate']; } ?>"><br>

Major: <br />
<input type="radio" name="major" value="CS" <?php if($_POST['major'] == 'CS') echo "checked" ?> >CS<br />
<input type="radio" name="major" value="EE" <?php if($_POST['major'] == 'EE') echo "checked" ?> >EE<br />
<input type="radio" name="major" value="other" <?php if($_POST['major'] == 'other') echo "checked" ?> >Other<br />
Courses: <br>

<?php
//Loops through every course and provides a select box
$query = "SELECT * FROM Course_T";
$courses = mysqli_query($dbc, $query)
    or die("Error fetching result");
$i = 0;
while($row=mysqli_fetch_assoc($courses)){
	$checked = "";
	if(isset($_POST['courses'][$i])){
		$checked = " checked ";
	}
	echo "<input type='checkbox' name='courses[$i]' value='" . $row['cID'] . "'" . $checked . ">" . $row['cName'] . "<br>";
	$i++;
}
?>

<input type="submit" name="formSubmit" value="Submit">
</form>

<a href="student_index.php">Return to index</a>

</body>
</html>
