import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'dart:math';
import 'package:huchao/component/oneCard.dart';
import 'package:huchao/component/twoCard.dart';
import 'package:huchao/component/threeCard.dart';
import 'package:dio/dio.dart';
import 'dart:convert';
import 'package:flutter_screenutil/flutter_screenutil.dart';

var doorCondition;

class Condition extends StatefulWidget {
  @override
  ConditionState createState() => new ConditionState();
}

class ConditionState extends State<Condition> {
  @override
  Widget build(BuildContext context) {
    return  new Scaffold(
      appBar: new AppBar(
        title: new Text("现状"),
        backgroundColor: Color.fromARGB(250, 100, 170, 255), //设置appbar背景颜色
        centerTitle: true, //设置标题是否局中
      ),
      body: MyHomePage(),
    );
  }
}

class DotsIndicator extends AnimatedWidget {
  DotsIndicator({
    this.controller,
    this.itemCount,
    this.onPageSelected,
    this.color: Colors.white,
  }) : super(listenable: controller);

  /// The PageController that this DotsIndicator is representing.
  final PageController controller;

  /// The number of items managed by the PageController
  final int itemCount;

  /// Called when a dot is tapped
  final ValueChanged<int> onPageSelected;

  /// The color of the dots.
  ///
  /// Defaults to `Colors.white`.
  final Color color;

  // The base size of the dots
  static const double _kDotSize = 8.0;

  // The increase in the size of the selected dot
  static const double _kMaxZoom = 2.0;

  // The distance between the center of each dot
  static const double _kDotSpacing = 25.0;

  Widget _buildDot(int index,int pageCount) {
    // 当前位置
    double currentPosition =
    ((controller.page ?? controller.initialPage.toDouble()) %
        pageCount.toDouble());

    // 计算变化曲线
    double selectedness = Curves.easeOut.transform(
      max(
        0.0,
        1.0 - (currentPosition - index).abs(),
      ),
    );

    // 从0点跳到最后一个时状态需要特殊处理
    if (currentPosition > pageCount - 1 && index == 0) {
      selectedness = 1 - (pageCount.toDouble() - currentPosition);
    }

    print('selectedness $index');
    print('selectedness $selectedness');
    print('selectedness $controller.page');
    print('selectedness $controller.initialPage');

    // 计算缩放大小
    double zoom = 1.0 + (_kMaxZoom - 1.0) * selectedness;

    return new Container(
      width: _kDotSpacing,
      child: new Center(
        child: new Material(
          color: color,
          type: MaterialType.circle,
          child: new Container(
            width: _kDotSize * zoom,
            height: _kDotSize * zoom,
            child: new InkWell(
              onTap: () => onPageSelected(index),
            ),
          ),
        ),
      ),
    );
  }

  Widget build(BuildContext context) {
    ScreenUtil.instance = ScreenUtil(width: 1080, height: 1920)..init(context);
    return new Row(
      mainAxisAlignment: MainAxisAlignment.center,
      children: new List<Widget>.generate(itemCount,(int index) {
        return _buildDot(index, itemCount);
      }),
    );
  }
}

class MyHomePage extends StatefulWidget {
  @override
  State createState() => new MyHomePageState();
}

class MyHomePageState extends State<MyHomePage> {
  final _controller = new PageController();
  static const _kDuration = const Duration(milliseconds: 300);
  static const _kCurve = Curves.ease;
  final _kArrowColor = Colors.black.withOpacity(0.8);

  final List<Widget> _pages = <Widget>[
    new ConstrainedBox(
      constraints: const BoxConstraints.expand(),
      child:OneCard(),
    ),
    new ConstrainedBox(
      constraints: const BoxConstraints.expand(),
      child:TwoCard(),
    ),
    new ConstrainedBox(
      constraints: const BoxConstraints.expand(),
      child:ThreeCard(),
    ),
  ];

  void initState() {
    super.initState();
    getDoor();
  }
  void getDoor()async{
    Dio dio = Dio();
    final response = await dio.get("http://106.54.116.153:8083/users/last");
    print(response);
    var data = jsonDecode(response.toString());
    print('wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww');
    setState(() {
      doorCondition = data['data']['time'];
      print(doorCondition);
    });
  }
  @override
  Widget build(BuildContext context) {

    return new Scaffold(
//      appBar: new AppBar(
//        title: new Text('PageControl'),
//      ),

        body: Center(
          child:new IconTheme(
            data: new IconThemeData(color: _kArrowColor),
            child: new Stack(
              children: <Widget>[
                new PageView.builder(
                  physics: new AlwaysScrollableScrollPhysics(),
                  controller: _controller,
                  itemBuilder: (BuildContext context, int index) {
//                    getDoor();
                    return _pages[index % _pages.length];
                  },
                ),
                new Positioned(
                  bottom: 0.0,
                  left: 0.0,
                  right: 0.0,
                  child: new Container(
                    color: Colors.grey[800].withOpacity(0.2),
                    padding: const EdgeInsets.all(20.0),
                    child: new Center(
                      child: new DotsIndicator(
                        controller: _controller,
                        itemCount: _pages.length,
                        onPageSelected: (int page) {
                          _controller.animateToPage(
                            page,
                            duration: _kDuration,
                            curve: _kCurve,
                          );
                        },
                      ),
                    ),
                  ),
                ),
              ],
            ),
          ),
        )
    );
  }
}

//class DisplayPage extends StatefulWidget {
//  @override
//  _DisplayPageState createState() => new _DisplayPageState();
//}
//
//class _DisplayPageState extends State<DisplayPage> {
//  static bool _isAddGradient = false;
//
//  final List descriptions = [
//    'tryenough.com',
//    'tryenough.com',
//    'tryenough.com',
//  ];
//
//  var decorationBox = DecoratedBox(
//    decoration: _isAddGradient
//        ? BoxDecoration(
//      gradient: LinearGradient(
//        begin: FractionalOffset.bottomRight,
//        end: FractionalOffset.topLeft,
//        colors: [
//          Color(0x00000000).withOpacity(0.9),
//          Color(0xff000000).withOpacity(0.01),
//        ],
//      ),
//    )
//        : BoxDecoration(),
//  );
//
//
//
//
//  @override
//  Widget build(BuildContext context) {
//    PageController controller = PageController(viewportFraction: 0.8);
//
//    controller.addListener((){
//
//    });
//
//    return Scaffold(
//      backgroundColor: Colors.black,
//      body: Center(
//        child: SizedBox.fromSize(
//          size: Size.fromHeight(550.0),
//          child: PageView.builder(
//            controller: controller,
//            itemCount: 3,
//            itemBuilder: (BuildContext context, int index) {
//              return Padding(
//                padding: EdgeInsets.symmetric(
//                  vertical: 16.0,
//                  horizontal: 8.0,
//                ),
//                child: GestureDetector(
//                  onTap: () {
//                    Scaffold.of(context).showSnackBar(SnackBar(
//                      backgroundColor: Colors.deepOrangeAccent,
//                      duration: Duration(milliseconds: 800),
//                      content: Center(
//                        child: Text(
//                          descriptions[index],
//                          style: TextStyle(fontSize: 25.0),
//                        ),
//                      ),
//                    ));
//                  },
//                  child: Material(
//                    elevation: 5.0,
//                    borderRadius: BorderRadius.circular(8.0),
//                    child: Stack(
//                      fit: StackFit.expand,
//                      children: [
//                        FlutterLogo(style: FlutterLogoStyle.stacked, colors: Colors.red),
//                        decorationBox,
//                      ],
//                    ),
//                  ),
//                ),
//              );
//            },
//          ),
//        ),
//      ),
//    );
//  }
//}
