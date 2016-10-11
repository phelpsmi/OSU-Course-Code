
<title>List All Students</title>
<?php

$dbhost = 'oniddb.cws.oregonstate.edu';
$dbname = 'phelpsmi-db';
$dbuser = 'phelpsmi-db';
$dbpass = 'kPMlMYXHsXV0VOML';

$dbc = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname)
    or die("Error connecting to database server");
    
$query = "SELECT * FROM Student_T";
$result = mysqli_query($dbc, $query)
    or die("Error fetching result");

echo "<a href='form.php'><h3>Create new student</h3></a>";
echo "<a href='course_index.php'><h3>View Courses</h3></a><br>";
while($row=mysqli_fetch_assoc($result)){
    echo "Student ID: " . $row['sID'] . "<br>";
    echo "Name: " . $row['firstName'] . ' ' . $row['last_name'] . "<br>";
    echo "E-mail: " . $row['email'] . '<br>'; 
    echo "Age: " . $row['bDate'] . '<br>';
    echo "Major: " . $row['major'] . '<br>';
    echo "<a href='student_view.php?sID=" . $row['sID'] . "'>View</a>";
    echo "<br><br>";
}

?>