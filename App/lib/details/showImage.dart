import 'package:flutter/material.dart';
import 'package:huchao/component/threeCard.dart';


class ShowImage extends StatelessWidget{
  @override
  Widget build(BuildContext context){
    return new Scaffold(
      appBar: new AppBar(
        title: new Text('人数图片'),
        backgroundColor: Color.fromARGB(250, 100, 170, 255),
        centerTitle: true,
      ),
      body: new OneImage(),
    );
  }
}

class OneImage extends StatefulWidget{
  @override
  OneImageState createState() => new OneImageState();
}

class OneImageState extends State<OneImage>{

//  void initState(){
//    super.initState();
//    getUrl();
//  }
//  getUrl() async{
//    var data = 'http://www.nestprotect.xyz/img/person.jpg';
//    setState(() {
//      url = data ;
//    });
//  }
  @override
  Widget build(BuildContext context){
    return new Container(
     alignment: const Alignment(0.0, 0.0),
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
        margin: new EdgeInsets.only(top: 70.0,bottom:50.0,left:10.0,right:10.0),
        child: new Column(
          mainAxisAlignment: MainAxisAlignment.start,
          children: <Widget>[
            new Padding(
              padding: new EdgeInsets.only(top: 30.0),
              child: new Text(
                '人数图片',
                style: new TextStyle(
                  fontSize: 30.0,
                  fontWeight: FontWeight.bold,
                ),
              ),
            ),
            new Padding(
              padding:new EdgeInsets.only(top: 30.0),
              child: new Container(
                width: 350.0,
                height: 350.0,
                margin:
                new EdgeInsets.only(bottom: 20.0),
//                decoration: BoxDecoration(
////                  image: DecorationImage(
////
////                    image: new AssetImage(
////                        'images/number.jpg',
////                    ),
////                    fit: BoxFit.cover,
////                  ),
////                ),
                child:new Image.network(
                  url,
                  width: 350,
                  height: 350,
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}

