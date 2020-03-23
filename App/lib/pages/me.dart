import 'package:flutter/material.dart';

class Me extends StatefulWidget {
  @override
  MeState createState() => new MeState();
}

class MeState extends State<Me> {
  @override
  Widget build(BuildContext context) {
    return new MaterialApp(
      debugShowCheckedModeBanner: false,
      home: new Scaffold(
        appBar: new AppBar(
          title: new Text("我的"),
          backgroundColor: Color.fromARGB(250, 100, 170, 255), //设置appbar背景颜色
          centerTitle: true, //设置标题是否局中
        ),
        body:new ListView(
          children: <Widget>[
            //个人信息部分
            new Container(
                color: Color.fromARGB(250, 100, 170, 255),
                child: new Padding(
                  padding: new EdgeInsets.only(top:20.0,bottom: 20.0),
                  child: new Column(
                    mainAxisAlignment: MainAxisAlignment.start,
                    children: <Widget>[
                          //头像
                          new Container(
                            width: 100.0,
                            height: 100.0,
                            margin:
                            new EdgeInsets.only(bottom: 20.0),
                            decoration: BoxDecoration(
                              image: DecorationImage(
                                image: new AssetImage('images/Old-Man.png'),
                                fit: BoxFit.cover,
                              ),
                              shape: BoxShape.circle,
                            ),
                          ),
                      Text(
                        '护巢',
                        style: new TextStyle(
                          fontSize: 20.0,
                        ),
                      )
                    ],
                  ),
                )
            ),
            new ListTile(
              //第二个功能项
                title: new Text('系统绑定'),
                leading: new Icon(Icons.settings_system_daydream),
              trailing: new Icon(Icons.arrow_forward_ios),
                ),
            //分割线控件
            new ListTile(
              //退出按钮
                title: new Text('警报设置'),
                leading: new Icon(Icons.add_alert),
              trailing: new Icon(Icons.arrow_forward_ios),
            ),
            //分割线控件
            new ListTile(
              //退出按钮
                title: new Text('帮助说明'),
                leading: new Icon(Icons.map),
              trailing: new Icon(Icons.arrow_forward_ios),
            ),
            //分割线控件
            new ListTile(
              //退出按钮
                title: new Text('意见反馈'),
                leading: new Icon(Icons.feedback),
              trailing: new Icon(Icons.arrow_forward_ios),
            ),
            //分割线控件
            new ListTile(
              //退出按钮
                title: new Text('关于我们'),
                leading: new Icon(Icons.group_add),
              trailing: new Icon(Icons.arrow_forward_ios),
            ),
            new ListTile(
              //退出按钮
                title: new Text('设置'),
                leading: new Icon(Icons.sync),
              trailing: new Icon(Icons.arrow_forward_ios),
            ),
            new ListTile(
              //退出按钮
                title: new Text('检测升级'),
                leading: new Icon(Icons.refresh),
              trailing: new Icon(Icons.arrow_forward_ios),
            ),
            new ListTile(
              //退出按钮
                title: new Text('更新说明'),
                leading: new Icon(Icons.info),
              trailing: new Icon(Icons.arrow_forward_ios),
            ),
          ],
        ),
      ),
    );
  }
}