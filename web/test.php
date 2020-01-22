<!DOCTYPE html>
<html>
<head>
    <title>Document</title>
</head>
<body>
    <table style='text-align:left;' border='1'>
    <tr><th>id</th><th>日期</th><th>时间</th></tr>
    <?php
        require 'connect.php';
        $sql = mysql_query("select * from fire");
        $datarow = mysql_num_rows($sql);
        for($i=0; $i < $datarow; $i++){
            $sql_arr = mysql_fetch_assoc($sql);
            $id = $sql_arr['uid'];
            $date = $sql_arr['date'];
            $time = $sql_arr['time'];
            echo "<tr><td>$id</td><td>$date</td><td>$time</td></tr>";
        }
    ?>
</table>
</body>
</html>