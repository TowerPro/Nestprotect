<?php
    $con = mysql_connect("your_ip_address","sql_usrname","sql_passwd");
    mysql_query("SET NAMES 'utf8'");
    mysql_query("SET CHARACTER SET utf8");
    if(!$con){
        die(mysql_error());
    }

    mysql_select_db("huchao",$con);
    ?>