
<title>Course List</title>
<?php

$dbhost = 'oniddb.cws.oregonstate.edu';
$dbname = 'phelpsmi-db';
$dbuser = 'phelpsmi-db';
$dbpass = 'kPMlMYXHsXV0VOML';

$dbc = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname)
    or die("Error connecting to database server");
    
$query = " SELECT *, COUNT(*) AS headcount FROM Course_T AS t1, Enrollment_T AS t2
 			WHERE t1.cID = t2.cID GROUP BY t1.cID";
$result = mysqli_query($dbc, $query)
    or die("Error fetching result");

echo "<a href='student_index.php'><h3>View Students</h3></a><br>";
while($row=mysqli_fetch_assoc($result)){
    echo "Course ID: " . $row['cID'] . "<br>";
    echo "Name: " . $row['cName'] . ' ' . $row['last_name'] . "<br>";
    echo "Credits: " . $row['credits'] . '<br>';
    echo "Students Enrolled: " . $row['headcount'] . '<br>';
    echo "<a href='course_view.php?cID=" . $row['cID'] . "'>View</a>";
    echo "<br><br>";
}

?>