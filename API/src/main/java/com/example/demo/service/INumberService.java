package com.example.demo.service;

import com.example.demo.bean.Number;

import java.util.List;

public interface INumberService {
    //获取所有的用户
    Number getLastNumber();

    List<Number> getAllNumber();
    //增
    int  addNumber(Number Number);
    //删
    int  deleteNumber(long id);
    //改
    int updateNumber(Number Number);
    //查
    Number queryNumber(long id);
}
