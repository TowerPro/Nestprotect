import 'package:flutter/material.dart';
import 'package:huchao/pages/condition.dart';
import 'package:huchao/pages/me.dart';
import 'package:huchao/login.dart';





void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: '护巢',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: LoginPage(),
    );
  }
}

class Huchao extends StatefulWidget {
  @override
  HuchaoState createState() => new HuchaoState();
}

class HuchaoState extends State<Huchao> with SingleTickerProviderStateMixin {
  TabController controller;

  @override
  void initState() {
    controller = new TabController(length: 2, vsync: this);
  }


  @override
  Widget build(BuildContext context) {
    return new MaterialApp(
      debugShowCheckedModeBanner: false,
      home: new Scaffold(
        body: new TabBarView(
          controller: controller,
          children: <Widget>[
            new Condition(),
            new Me(),
          ],
        ),
        bottomNavigationBar: new Material(
          color: Colors.white,
          child: new TabBar(
            controller: controller,
            labelColor: Colors.deepPurpleAccent,
            unselectedLabelColor: Colors.black26,
            tabs: <Widget>[
              new Tab(
                text: "现状",
                icon: new Icon(Icons.blur_on),
              ),
              new Tab(
                text: "我的",
                icon: new Icon(Icons.people),
              ),
            ],
          ),
        ),
      ),
    );
  }
}