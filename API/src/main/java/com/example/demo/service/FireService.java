package com.example.demo.service;

import com.example.demo.bean.Fire;
import com.example.demo.repository.JpaFireRepository;
import com.example.demo.result.ErrorCode;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;
import org.springframework.stereotype.Service;


import javax.annotation.Resource;
import java.util.List;

@Service
public class FireService implements IFireService {

    @Autowired
    JpaFireRepository jpaFireRepository;

    @Override
    public Fire getLastFire() {
        List<Fire> Fires = jpaFireRepository.findAll();
        System.out.println(Fires.toString());
        Fire lastFire;
        System.out.println(Fires.size());
        int num;
        num = Fires.size();
        lastFire = Fires.get(num-1);
        System.out.println(lastFire);
        return lastFire;
    }
    @Override
    public List<Fire> getAllFire() {
        List<Fire> Fires = jpaFireRepository.findAll();
        System.out.println(Fires.toString());
        return Fires;
    }

    @Override
    public int addFire(Fire Fire) {
        if (jpaFireRepository.existsById(Fire.getId())){
            System.out.println("Fire  is existed");
            return ErrorCode.EXISTUSER;
        }
        Fire saveFire = jpaFireRepository.save(Fire);
        if (saveFire != null && saveFire.getId() == Fire.getId()) {
            System.out.println("save success");
            return ErrorCode.ADDSUCCESS;
        } else {
            System.out.println("save failure");
            return ErrorCode.ADDFAIL;
        }
    }

    @Override
    public int deleteFire(long id) {
        if (jpaFireRepository.existsById(id)) {
            jpaFireRepository.deleteById(id);
            System.out.println("删除成功");
            return ErrorCode.DELETESUCCESS;
        }
        System.out.println("删除失败");
        return ErrorCode.NOTEXISTUSER;
    }

    @Override
    public int updateFire(Fire Fire) {
        if (jpaFireRepository.existsById(Fire.getId())){
            jpaFireRepository.save(Fire);
            System.out.println("更新成功");
            return ErrorCode.UPDATESUCCESS;
        }
        System.out.println("更新失败");
        return ErrorCode.UPDATEFAIL;
    }

    @Override
    public Fire queryFire(long id) {
        Fire Fire = null;
        if (jpaFireRepository.existsById(id)){
            Fire = jpaFireRepository.findById(id).get();
            System.out.println(Fire.toString());
        }
        return Fire;
    }
}
