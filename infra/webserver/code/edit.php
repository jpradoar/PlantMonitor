<?php
// including the database connection file
include_once("config.php");

if(isset($_POST['update']))
{	

	$id = mysqli_real_escape_string($mysqli, $_POST['id']);
	
	$name = mysqli_real_escape_string($mysqli, $_POST['name']);
	$data1 = mysqli_real_escape_string($mysqli, $_POST['data1']);
	$data2 = mysqli_real_escape_string($mysqli, $_POST['data2']);	
	
	// checking empty fields
	if(empty($name) || empty($data1) || empty($data2)) {	
			
		if(empty($name)) {
			echo "<font color='red'>Name field is empty.</font><br/>";
		}
		
		if(empty($data1)) {
			echo "<font color='red'>data1 field is empty.</font><br/>";
		}
		
		if(empty($data2)) {
			echo "<font color='red'>data2 field is empty.</font><br/>";
		}		
	} else {	
		//updating the table
		$result = mysqli_query($mysqli, "UPDATE users SET name='$name',data1='$data1',data2='$data2' WHERE id=$id");
		
		//redirectig to the display pdata1. In our case, it is index.php
		header("Location: index.php");
	}
}
?>
<?php
//getting id from url
$id = $_GET['id'];

//selecting data associated with this particular id
$result = mysqli_query($mysqli, "SELECT * FROM users WHERE id=$id");

while($res = mysqli_fetch_array($result))
{
	$name = $res['name'];
	$data1 = $res['data1'];
	$data2 = $res['data2'];
}
?>
<html>
<head>	
	<title>Edit Data</title>
</head>

<body>
	<a href="index.php">Home</a>
	<br/><br/>
	
	<form name="form1" method="post" action="edit.php">
		<table border="0">
			<tr> 
				<td>Name</td>
				<td><input type="text" name="name" value="<?php echo $name;?>"></td>
			</tr>
			<tr> 
				<td>data1</td>
				<td><input type="text" name="data1" value="<?php echo $data1;?>"></td>
			</tr>
			<tr> 
				<td>data2</td>
				<td><input type="text" name="data2" value="<?php echo $data2;?>"></td>
			</tr>
			<tr>
				<td><input type="hidden" name="id" value=<?php echo $_GET['id'];?>></td>
				<td><input type="submit" name="update" value="Update"></td>
			</tr>
		</table>
	</form>
</body>
</html>
