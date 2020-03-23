import 'package:flutter/material.dart';
import 'package:huchao/details/door.dart';
import 'package:flutter_screenutil/flutter_screenutil.dart';
import 'package:huchao/login.dart';
import 'package:dio/dio.dart';
import 'dart:convert';

class OneCard extends StatefulWidget{
  @override
  OneCardState createState() => new OneCardState();
}

class OneCardState extends State<OneCard>{

  DateTime _dateTime;

  void _getDate(){
    _dateTime = new DateTime.now();
    if(doorDate == (_dateTime.year.toString()+"-"+_dateTime.month.toString()+"-"+_dateTime.day.toString()) &&
    doorTime == (_dateTime.hour.toString()+"-"+_dateTime.minute.toString()+"-"+_dateTime.second.toString())){
      doorCondition = "开";
    }
    else{
      doorCondition = "关";
    }
  }
  @override
  void initState() {
    super.initState();
    getLastDoor();
    _getDate();
  }

  getLastDoor() async{
    Dio dio = Dio();
    final response = await dio.get("http://106.54.116.153:8083/Doors/last");
    print(response);
    var data = jsonDecode(response.toString());
    setState(() {
      doorDate = data['data']['date'];
      doorTime = data['data']['time'];
    });
  }


  @override
  Widget build(BuildContext context){
    ScreenUtil.instance = ScreenUtil(width: 1080, height: 1920)..init(context);
    return new MaterialApp(
      debugShowCheckedModeBanner: false,
      home: new Container(
        decoration: BoxDecoration(
          gradient: LinearGradient(
            begin: Alignment.topLeft,
            end: Alignment.bottomRight,
            colors: [
              Color.fromARGB(250, 150, 200, 240),
              Colors.white,
            ],
          ),
        ),
        child: new Card(
          color: Color.fromARGB(255, 255, 255, 255),
          elevation: 10.0,
          shape: const RoundedRectangleBorder(
              borderRadius: BorderRadius.all(Radius.circular(14.0))
          ),
          margin: new EdgeInsets.only(top: ScreenUtil().setHeight(150.0),bottom:ScreenUtil().setHeight(150.0)
              ,left:ScreenUtil().setWidth(170.0),right:ScreenUtil().setWidth(170.0)),
          child: new Column(
            mainAxisAlignment: MainAxisAlignment.start,
            children: <Widget>[
              new Padding(
                padding: new EdgeInsets.only(top: ScreenUtil().setHeight(150.0)),
                child: new Text(
                  '门',
                  style: new TextStyle(
                    fontSize: ScreenUtil(allowFontScaling: true).setSp(75.0),
                    fontWeight: FontWeight.bold,
                  ),
                ),
              ),
              new Padding(
                padding:new EdgeInsets.only(top: ScreenUtil().setHeight(100.0)),
                child: new MaterialButton(
                  onPressed: (){
                    Navigator.push(
                      context,
                      new MaterialPageRoute(builder: (context) => new DoorPage()),
                    );
                  },
                  child: new Container(
                    width: ScreenUtil().setWidth(300.0),
                    height: ScreenUtil().setHeight(300.0),
                    margin:
                    new EdgeInsets.only(bottom: ScreenUtil().setHeight(50.0)),
                    decoration: BoxDecoration(
                      image: DecorationImage(
                        image: new ExactAssetImage('images/door.png'),
                        fit: BoxFit.cover,
                      ),
                      shape: BoxShape.circle,
                    ),
                  ),
                ),
              ),
              new Padding(
                  padding: new EdgeInsets.only(top: ScreenUtil().setHeight(50.0)),
                  child: new Column(
                    mainAxisAlignment: MainAxisAlignment.start,
                    children: <Widget>[
                      new RaisedButton(
                        color: Color.fromARGB(250, 150, 200, 240),
                        onPressed: (){
                          getLastDoor();
                          _getDate();
                        },
                        child: new Text(
                          doorDate,
                          style: new TextStyle(
                            fontSize: ScreenUtil(allowFontScaling: true).setSp(50.0),
                          ),
                        ),
                      ),
                      new RaisedButton(
                        color: Color.fromARGB(250, 150, 200, 240),
                        onPressed: (){
                          getLastDoor();
                          _getDate();
                        },
                        child: new Text(
                          doorTime,
                          style: new TextStyle(
                            fontSize: ScreenUtil(allowFontScaling: true).setSp(50.0),
                          ),
                        ),
                      )
                    ],
                  )
              ),
            ],
          ),
        ),
      ),
    );
  }
}

