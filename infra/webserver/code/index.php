<!DOCTYPE html>
<html>
<head>
<style>
</style>
</head>
<h1>Api User Database</h1>
<body>
<?php

//including the database connection file
include_once("config.php");

//fetching data in descending order (lastest entry first)
$result = mysqli_query($mysqli, "SELECT * FROM users ORDER BY id DESC"); // using mysqli_query instead
?>

<html>
<head>	
	<title>Homepage</title>
</head>

<body>
<a href="add.html"><button>Add New</button></a><a href="localhost:3000" target="_blank"><button>Graph</button></a><br/><br/><br/><br/>

	<table width='80%' border=1>

	<tr bgcolor='#CCCCCC'>
		<td>Name</td>
		<td>User</td>
		<td>Pass</td>
		<td>Update</td>
	</tr>
	<?php 
	while($res = mysqli_fetch_array($result)) { 		
		echo "<tr>";
		echo "<td>".$res['name']."</td>";
		echo "<td>".$res['user']."</td>";
		echo "<td class='hidetext'>".$res['pass']."</td>";	
		echo "<td><button><a href=\"edit.php?id=$res[id]\">Edit</a></button> <button><a href=\"delete.php?id=$res[id]\" onClick=\"return confirm('Are you sure you want to delete?')\">Delete</a></button></td>";		
	}
	?>
	</table>
</body>
</html>
