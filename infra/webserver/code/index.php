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
<button><a href="add.html">Add New Data</a></button><button><a href="localhost:3000" target="_blank">Graph</a></button><br/><br/><br/><br/>

	<table width='80%' border=1>

	<tr bgcolor='#CCCCCC'>
		<td>Name</td>
		<td>data1</td>
		<td>data2</td>
		<td>Update</td>
	</tr>
	<?php 
	while($res = mysqli_fetch_array($result)) { 		
		echo "<tr>";
		echo "<td>".$res['name']."</td>";
		echo "<td>".$res['data1']."</td>";
		echo "<td>".$res['data2']."</td>";	
		echo "<td><button><a href=\"edit.php?id=$res[id]\">Edit</a></button> <button><a href=\"delete.php?id=$res[id]\" onClick=\"return confirm('Are you sure you want to delete?')\">Delete</a></button></td>";		
	}
	?>
	</table>
</body>
</html>
