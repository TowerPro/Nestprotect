import 'package:flutter/material.dart';
import 'package:dio/dio.dart';
import 'dart:convert';
import 'package:huchao/login.dart';


var num;

class NumberPage extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return new  Scaffold(
      appBar: new AppBar(
        title: new Text("人数详情"),
        backgroundColor: Color.fromARGB(250, 100, 170, 255), //设置appbar背景颜色
        centerTitle: true, //设置标题是否局中
      ),
      body: Number(),
    );
  }
}
class Number extends StatefulWidget {
  @override
  NumberState createState() => new NumberState();
}

class NumberState extends State<Number>{

  void initState() {
    super.initState();
    getAllNumber();
  }

  int getItemCount(){
    if(numberAllCondition.isEmpty){
      return 5;
    }
    num = numberAllCondition.length;
    return numberAllCondition.length;
  }

  Widget getItemWidget(int position){
    if(numberAllCondition.isEmpty){
      return getEmptyLoadingWidget();
    }
    return getRow(position);
  }


  Widget getRow(int i) {
    return Padding(
      padding: EdgeInsets.all(10.0),
      child: Card(
        child: ListTile(
          leading: CircleAvatar(
            backgroundImage:AssetImage ('images/camera.png'),
          ),
          title: Text(
            " ${numberAllCondition[num-i-1]["time"]}",
            maxLines: 1,
            style: TextStyle(
              color: Colors.blue,
            ),
            semanticsLabel: 'semanticsLabel',
          ),
          subtitle: Text(" ${numberAllCondition[num-i-1]["date"]}"),
          trailing: Text(
            '${numberAllCondition[num-i-1]["peoplenum"]}',
            style: new TextStyle(
              fontSize: 25.0,
            ),
          ),
        ),
      ),
    );
  }

  Widget getEmptyLoadingWidget() {
    return Padding(
      padding: EdgeInsets.all(10.0),
      child: Card(
        child: Column(
          children: <Widget>[
            ListTile(
              leading: CircleAvatar(
                child: Text('**'),
              ),
              title: Text(
                "******",
                maxLines: 1,
                style: TextStyle(
                  color: Colors.blue,
                ),
                semanticsLabel: 'semanticsLabel',
              ),
              subtitle: Text("******"),
              trailing: Text('******'),
            ),
            Text('努力加载中...'),
          ],
        ),
      ),
    );
  }

  getAllNumber() async{
    Dio dio = Dio();
    final response = await dio.get("http://106.54.116.153:8083/Numbers/all");
    print(response);
    var data = jsonDecode(response.toString());
    setState(() {
      numberAllCondition = data["data"]["Numbers"];
      print(num);
    });
  }

  @override
  Widget build(BuildContext context) {
    return  new ListView.builder(
      itemCount: getItemCount(),
      itemBuilder: (BuildContext context, int position){
        return getItemWidget(position);
      },
    );
  }
}