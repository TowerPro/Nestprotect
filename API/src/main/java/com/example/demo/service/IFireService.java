package com.example.demo.service;

import com.example.demo.bean.Fire;

import java.util.List;

public interface IFireService {
    //获取所有的用户
    Fire getLastFire();

    List<Fire> getAllFire();
    //增
    int  addFire(Fire Fire);
    //删
    int  deleteFire(long id);
    //改
    int updateFire(Fire Fire);
    //查
    Fire queryFire(long id);
}
