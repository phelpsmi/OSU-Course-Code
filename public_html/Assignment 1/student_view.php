<?php

if (isset($_GET['message'])) {
    print $_GET['message'];
}

$dbhost = 'oniddb.cws.oregonstate.edu';
$dbname = 'phelpsmi-db';
$dbuser = 'phelpsmi-db';
$dbpass = 'kPMlMYXHsXV0VOML';

$dbc = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname)
    or die("Error connecting to database server");
  
  $sID = $_GET['sID'];
  $query = "SELECT * FROM `Student_T` WHERE sID = $sID";
  $result = mysqli_query($dbc, $query) or die("Could not select student");
  $student = mysqli_fetch_assoc( $result );
  
  echo "<title>" . $student['lastName'] . ", " . $student['first_name'] . "</title>";
  echo "<h1>" . $student['firstName'] . " " . $student['last_name'] . "</h1>";
  echo "<h3>Student ID: " . $student['sID'] . "</h3>";
  echo "<h3>Email: " . $student['email'] . "</h3>";
  echo "<h3>Birthdate: " . $student['bDate'] . "</h3>";
  echo "<h3>Major: " . $student['major'] . "</h3>";

  $query = "SELECT * FROM Enrollment_T WHERE sID = $sID";
  $result = mysqli_query($dbc, $query) or die("Query failed: $query");

  echo "<table>";
  echo "<tr>";
  echo "<td>Course</td>";
  echo "<td>Credits</td>";
  echo "<td>Term</td>";
  echo "<td>Grade</td>";
  echo "</tr>";

  while($registration = mysqli_fetch_assoc($result)){
    $cID = $registration[cID];
    $query = "SELECT * FROM Course_T WHERE cID = '$cID'";
    $course = mysqli_fetch_assoc(mysqli_query($dbc, $query));
    echo "<tr><td>" . $course['cName'] . "</td><td>" . $course['credits'] . "</td><td>
          ". $registration['term'] . "</td><td>" . $registration['grade'] . "</td></tr>";
  }

  echo "</table></br>";

  echo "<a href='update.php?sID=" . $student['sID'] . "'>Edit</a><br>";

  echo "<a href='student_index.php'>Back to student index</a>";
  
?>

