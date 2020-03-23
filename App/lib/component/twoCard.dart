import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:huchao/details/kitchen.dart';
import 'package:dio/dio.dart';
import 'package:flutter_screenutil/flutter_screenutil.dart';
import 'package:huchao/login.dart';


class TwoCard extends StatefulWidget{
  @override
  TwoCardState createState() => new TwoCardState();
}

class TwoCardState extends State<TwoCard>{

  DateTime _dateTime;

  void _getDate(){
    _dateTime = new DateTime.now();
    if(fireDate == (_dateTime.year.toString()+"-"+_dateTime.month.toString()+"-"+_dateTime.day.toString()) &&
        fireTime == (_dateTime.hour.toString()+"-"+_dateTime.minute.toString()+"-"+_dateTime.second.toString())){
      fireCondition = "开";
    }
    else{
      fireCondition = "关";
    }
  }
  @override
  void initState() {
    super.initState();
    getLastFire();
    _getDate();
  }

  getLastFire() async{
    Dio dio = Dio();
    final response = await dio.get("http://106.54.116.153:8083/Fires/last");
    print(response);
    var data = jsonDecode(response.toString());
    setState(() {
      fireDate = data['data']['date'];
      fireTime = data['data']['time'];
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
          margin: new EdgeInsets.only(top: ScreenUtil().setHeight(150.0),bottom:ScreenUtil().setHeight(150.0),
              left:ScreenUtil().setWidth(170.0),right:ScreenUtil().setWidth(170.0)),
          child: new Column(
            mainAxisAlignment: MainAxisAlignment.start,
            children: <Widget>[
              new Padding(
                padding: new EdgeInsets.only(top: ScreenUtil().setHeight(150.0)),
                child: new Text(
                  '灶台',
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
                      new MaterialPageRoute(builder: (context) => new FirePage()),
                    );
                  },
                  child: new Container(
                    width: ScreenUtil().setWidth(300.0),
                    height: ScreenUtil().setWidth(300.0),
                    margin:
                    new EdgeInsets.only(bottom: ScreenUtil().setHeight(50.0)),
                    decoration: BoxDecoration(
                      image: DecorationImage(
                        image: new ExactAssetImage('images/kitchen.png'),
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
                          getLastFire();
                          _getDate();
                        },
                        child: new Text(
                          fireDate,
                          style: new TextStyle(
                            fontSize: ScreenUtil(allowFontScaling: true).setSp(50.0),
                          ),
                        ),
                      ),
                      new RaisedButton(
                        color: Color.fromARGB(250, 150, 200, 240),
                        onPressed: (){
                          getLastFire();
                          _getDate();
                        },
                        child: new Text(
                          fireTime,
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

