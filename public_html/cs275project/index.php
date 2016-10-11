<?php
session_start();

if($_POST['formSubmit'] == "Submit"){
	$_SESSION['id'] = $_POST['pass'];
}
if($_SESSION['id'] == 'password'){
	header("Location: main");
}

?>



<h2>Please enter the administration passcode</h2>
<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>" method="POST">
Passcode: <input type="text" name="pass"><br>

<input type="submit" name="formSubmit" value="Submit">
</form>