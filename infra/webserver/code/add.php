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
	$data1 = mysqli_real_escape_string($mysqli, $_POST['data1']);
	$data2 = mysqli_real_escape_string($mysqli, $_POST['data2']);
		
	// checking empty fields
	if(empty($name) || empty($data1) || empty($data2)) {
				
		if(empty($name)) {
			echo "<font color='red'>Name field is empty.</font><br/>";
		}
		
		if(empty($data1)) {
			echo "<font color='red'>Age field is empty.</font><br/>";
		}
		
		if(empty($data2)) {
			echo "<font color='red'>Email field is empty.</font><br/>";
		}
		
		//link to the previous pdata1
		echo "<br/><a href='javascript:self.history.back();'>Go Back</a>";
	} else { 
		// if all the fields are filled (not empty) 
			
		//insert data to database	
		$result = mysqli_query($mysqli, "INSERT INTO users(name,data1,data2) VALUES('$name','$data1','$data2')");
		
		//display success messdata1
		echo "<font color='green'>Data added successfully.";
		echo "<br/><a href='index.php'>View Result</a>";
	}
}
?>
</body>
</html>
