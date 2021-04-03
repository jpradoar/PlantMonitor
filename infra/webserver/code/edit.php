<?php
// including the database connection file
include_once("config.php");

if(isset($_POST['update']))
{	

	$id = mysqli_real_escape_string($mysqli, $_POST['id']);
	
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
	} else {	
		//updating the table
		$result = mysqli_query($mysqli, "UPDATE users SET name='$name',user='$user',pass='$pass' WHERE id=$id");
		
		//redirectig to the display puser. In our case, it is index.php
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
	$user = $res['user'];
	$pass = $res['pass'];
}
?>
<html>
<head>	
	<title>Edit Data</title>
</head>

<body>
	 <a href="index.php"><button>Home</button></a>
	<br/><br/>
	
	<form name="form1" method="post" action="edit.php">
		<table border="0">
			<tr> 
				<td>Name</td>
				<td><input type="text" name="name" value="<?php echo $name;?>"></td>
			</tr>
			<tr> 
				<td>User</td>
				<td><input type="text" name="user" value="<?php echo $user;?>"></td>
			</tr>
			<tr> 
				<td>Pass</td>
				<td><input type="password" name="pass" value="<?php echo $pass;?>"></td>
			</tr>
			<tr>
				<td><input type="hidden" name="id" value=<?php echo $_GET['id'];?>></td>
				<td><input type="submit" name="update" value="Update"></td>
			</tr>
		</table>
	</form>
</body>
</html>
