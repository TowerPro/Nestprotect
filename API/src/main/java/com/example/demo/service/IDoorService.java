package com.example.demo.service;

import com.example.demo.bean.Door;

import java.util.List;

public interface IDoorService {
    //获取所有的用户
    Door getLastDoor();

    List<Door> getAllDoor();
    //增
    int  addDoor(Door Door);
    //删
    int  deleteDoor(long id);
    //改
    int updateDoor(Door Door);
    //查
    Door queryDoor(long id);
}
