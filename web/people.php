<!DOCTYPE html>
<html lang="en">
<head>
        <meta charset="utf-8"/>
        <title>人数检测管理</title>
        <link rel="stylesheet" href="css/style.css">
        <link rel="shortcut icon" href="img/home.jpg">
</head>
<body>
        <div class="g-hd">
                <!-- 导航 -->
                <div class="m-hd f-pr f-cb">
                    <div class="title f-fl"><h1 class="u-title-en f-fl">护巢</h1><span class="f-fl"></span><h1 class="u-title-ch f-fl">NestProtect</h1></div>
                    <div class="usrAtt f-fl "><div class="usrAttOp f-fl" onclick="loginYN()"><span class="usrAttText">关注</span></div><p class="usrAttStatis f-fl"></p></div>
                    <!-- <div class="usrAtt-af f-fl " style="display:none;"><div class="usrAttOp f-fl"><span class="usrAttText">已关注</span><a href="javascript:attCancel();" class="usrAttCancel">取消</a></div><p class="usrAttStatis f-fl">粉丝46</p></div>
                    <div class="nav f-fr"><a href="http://open.163.com/"  target="_blank">网易公开课</a><a href="http://study.163.com/"  target="_blank">云课堂</a><a href="http://www.icourse163.org/"  target="_blank">中国大学MOOC</a><a href="" class="search"></a></div> -->
                </div>
            </div>
            
        <div class="g-ft2">
            <h2>家庭人数实时显示</h2>
            <h3>人数记录 </h3>
            <table width="1000" height="240" border="2" bordercolor="gray" style='text-align:center;'>
                <tr>
                        <td>日期</td>
                        <td>时间</td>
                        <td>人数</td>
                </tr>
                <?php
                            require 'connect.php';
                            $sql = mysql_query("select * from people order by uid desc limit 10");
                            $datarow = mysql_num_rows($sql);
                            for($i=0; $i < $datarow; $i++){
                                $sql_arr = mysql_fetch_assoc($sql);
                                $date = $sql_arr['date'];
                                $time = $sql_arr['time'];
                                $peoplenum = $sql_arr['peoplenum'];
                                echo "<tr><td>$date</td><td>$time</td><td>$peoplenum</td></tr>";
                            }
                ?>
            </table>
        </div>

            <div class="g-ft">
                    <div class="m-ftwrap f-pr f-cb">
                        <div class="ftleft f-fl">
                            <div class="title f-cb"><h1 class="u-title-en f-fl">护巢</h1><span class="f-fl"></span><h1 class="u-title-ch f-fl">Nestprotect</h1></div>
                            <p class="cprt">浙江工商大学信息与电子工程学院 IEE</br><a class="link" href="http://www.beian.miit.gov.cn">浙ICP备19040838号-1</a></p>
                        </div>
                        <div class="ftright f-fr f-cb">
                            <div class="link f-fl">
                                <p>友情链接：</p>
                                <a href="http://www.hzic.edu.cn/"  target="_blank">浙江工商大学</a></br>
                                <a href="http://iee.zjgsu.edu.cn/"  target="_blank">浙江工商大学信息与电子工程学院</a></br>
                                <a href="http://www.NestProtect.xyz/"  target="_blank">护巢NestProtect</a>
                            </div>
                            <div class="about f-fl">
                                <p>我们：</p>
                                <a target="_blank">关于</a></br>
                                <a target="_blank">联系</a></br>
                                <a target="_blank">关注</a>
                            </div>
                            <div class="more f-fl">
                                <p>更多：</p>
                                <a target="_blank">常见问题</a></br>
                                <a target="_blank">意见反馈</a>
                            </div>
                        </div>
                    </div>
                </div>
                <script src="js/md5.js" type="text/javascript"></script>
                <script src="js/main.js" type="text/javascript"></script>

</body>
</html>