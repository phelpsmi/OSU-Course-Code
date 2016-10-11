<?php
$dbhost = 'oniddb.cws.oregonstate.edu';
$dbname = 'phelpsmi-db';
$dbuser = 'phelpsmi-db';
$dbpass = 'kPMlMYXHsXV0VOML';

$dbc = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname)
    or die("Error connecting to database server");
  
  $cID = $_GET['cID'];
  $query = "SELECT * FROM Course_T WHERE cID = '$cID'";
  $result = mysqli_query($dbc, $query) or die("this failed: $query");
  $course = mysqli_fetch_assoc( $result );
  
  echo "<title>" . $course['cName'] . "</title>";
  echo "<h2>" . $course['cName'] . "</h2>";
  echo "<h4>Course ID: " . $course['cID'] . "</h4>";
  echo "<h4>Credits: " . $course['credits'] . "</h4>";
  echo "<h4>Course Description: " . $course['description'] . "</h4>";

  echo "<table>";
  echo "<tr>";
  echo "<td>Student ID</td>";
  echo "<td>Grade</td>";
  echo "<td>Term</td>";
  echo "</tr>";

  $query = " SELECT * FROM Course_T AS t1, Enrollment_T AS t2, Student_T AS t3
              WHERE t1.cID = t2.cID AND t2.sID = t3.sID AND t1.cID = $cID";
  $result = mysqli_query($dbc,$query) or die("this failed: $query");
  while($registration = mysqli_fetch_assoc($result)){
    echo "<tr><td>" . $registration['sID'] . "</td><td>" . $registration['grade'] . "</td><td>
          ". $registration['term'] . "</td></tr>";
  }

  echo "</table>";

  echo "<a href='course_index.php'>Back to course index</a>";
  
?>

