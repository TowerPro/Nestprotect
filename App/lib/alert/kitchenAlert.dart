import 'package:flutter/material.dart';

class KitchenAlert extends StatefulWidget{
  @override
  KitchenAlertState createState() => new KitchenAlertState();
}

class KitchenAlertState extends State<KitchenAlert>{
  @override
  Widget build(BuildContext context){
    return new Container(
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
        margin: new EdgeInsets.only(top: 50.0,bottom:50.0,left:70.0,right:70.0),
        child: new Column(
          mainAxisAlignment: MainAxisAlignment.start,
          children: <Widget>[
            new Padding(
              padding: new EdgeInsets.only(top: 30.0),
              child: new Text(
                '灶台',
                style: new TextStyle(
                  fontSize: 30.0,
                  fontWeight: FontWeight.bold,
                ),
              ),
            ),
            new Padding(
              padding:new EdgeInsets.only(top: 30.0),
              child: new Container(
                width: 200.0,
                height: 200.0,
                margin:
                new EdgeInsets.only(bottom: 20.0),
                decoration: BoxDecoration(
                  image: DecorationImage(
                    image: new ExactAssetImage('images/alert.png'),
                    fit: BoxFit.cover,
                  ),
                  shape: BoxShape.circle,
                ),
              ),
            ),
            new Padding(
              padding: new EdgeInsets.only(top: 50.0),
              child: new Text(
                '灶台明火已开3分钟',
                style: new TextStyle(
                  fontSize: 25.0,
                ),
              ),
            )
          ],
        ),
      ),
    );
  }
}

