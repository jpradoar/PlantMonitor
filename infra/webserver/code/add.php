<html>
<head>
	<title>Add Data</title>
</head>

<body>
<?php
//including the database connection file
include_once("config.php");

if(isset($_POST['Submit'])) {	
	$name = mysqli_real_escape_string($mysqli, $_POST['name']);
	$user = mysqli_real_escape_string($mysqli, $_POST['user']);
	$pass = mysqli_real_escape_string($mysqli, $_POST['pass']);
		
	// checking empty fields
	if(empty($name) || empty($user) || empty($pass)) {
				
		if(empty($name)) {
			echo "<font color='red'>Name field is empty.</font><br/>";
		}
		
		if(empty($user)) {
			echo "<font color='red'>User field is empty.</font><br/>";
		}
		
		if(empty($pass)) {
			echo "<font color='red'>Pass field is empty.</font><br/>";
		}
		
		//link to the previous puser
		echo "<br/><a href='javascript:self.history.back();'><button>Go Back</button></a>";
	} else { 
		// if all the fields are filled (not empty) 
			
		//insert data to database	
		$result = mysqli_query($mysqli, "INSERT INTO users(name,user,pass) VALUES('$name','$user','$pass')");
		
		//display success messuser
		echo "<font color='green'>Data added successfully.";
		echo "<br/><a href='index.php'>View Result</a>";
	}
}
?>
</body>
</html>
