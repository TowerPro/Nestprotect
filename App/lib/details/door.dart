import 'package:flutter/material.dart';
import 'package:dio/dio.dart';
import 'dart:convert';
import 'package:huchao/login.dart';


var num;
class DoorPage extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return new  Scaffold(
      appBar: new AppBar(
        title: new Text("开门详情"),
        backgroundColor: Color.fromARGB(250, 100, 170, 255), //设置appbar背景颜色
        centerTitle: true, //设置标题是否局中
      ),
      body: Door(),
    );
  }
}
class Door extends StatefulWidget {
  @override
  DoorState createState() => new DoorState();
}

class DoorState extends State<Door>{

  void initState() {
    super.initState();
    getAllDoor();
  }

  int getItemCount(){
    if(doorAllCondition.isEmpty){
      return 5;
    }
    num = doorAllCondition.length;
    return doorAllCondition.length;
  }

  Widget getItemWidget(int position){
    if(doorAllCondition.isEmpty){
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
            backgroundImage:AssetImage ('images/door.png'),
          ),
          title: Text(
            " ${doorAllCondition[num-i-1]["time"]}",
            maxLines: 1,
            style: TextStyle(
              color: Colors.blue,
            ),
            semanticsLabel: 'semanticsLabel',
          ),
          subtitle: Text(" ${doorAllCondition[num-i-1]["date"]}"),
          trailing: Text('${doorAllCondition[num-i-1]["id"].toString()}'),
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

  getAllDoor() async{
    Dio dio = Dio();
    final response = await dio.get("http://106.54.116.153:8083/Doors/all");
    print(response);
    var data = jsonDecode(response.toString());
    setState(() {
      doorAllCondition = data["data"]["Doors"];
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