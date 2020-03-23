package com.example.demo.service;

import com.example.demo.bean.Number;
import com.example.demo.repository.JpaNumberRepository;
import com.example.demo.result.ErrorCode;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;
import org.springframework.stereotype.Service;


import javax.annotation.Resource;
import java.util.List;

@Service
public class NumberService implements INumberService {

    @Autowired
    JpaNumberRepository jpaNumberRepository;

    @Override
    public Number getLastNumber() {
        List<Number> Numbers = jpaNumberRepository.findAll();
        System.out.println(Numbers.toString());
        Number lastNumber;
        System.out.println(Numbers.size());
        int num;
        num = Numbers.size();
        lastNumber = Numbers.get(num-1);
        System.out.println(lastNumber);
        return lastNumber;
    }
    @Override
    public List<Number> getAllNumber() {
        List<Number> Numbers = jpaNumberRepository.findAll();
        System.out.println(Numbers.toString());
        return Numbers;
    }

    @Override
    public int addNumber(Number Number) {
        if (jpaNumberRepository.existsById(Number.getUid())){
            System.out.println("Number  is existed");
            return ErrorCode.EXISTUSER;
        }
        Number saveNumber = jpaNumberRepository.save(Number);
        if (saveNumber != null && saveNumber.getUid() == Number.getUid()) {
            System.out.println("save success");
            return ErrorCode.ADDSUCCESS;
        } else {
            System.out.println("save failure");
            return ErrorCode.ADDFAIL;
        }
    }

    @Override
    public int deleteNumber(long id) {
        if (jpaNumberRepository.existsById(id)) {
            jpaNumberRepository.deleteById(id);
            System.out.println("删除成功");
            return ErrorCode.DELETESUCCESS;
        }
        System.out.println("删除失败");
        return ErrorCode.NOTEXISTUSER;
    }

    @Override
    public int updateNumber(Number Number) {
        if (jpaNumberRepository.existsById(Number.getUid())){
            jpaNumberRepository.save(Number);
            System.out.println("更新成功");
            return ErrorCode.UPDATESUCCESS;
        }
        System.out.println("更新失败");
        return ErrorCode.UPDATEFAIL;
    }

    @Override
    public Number queryNumber(long id) {
        Number Number = null;
        if (jpaNumberRepository.existsById(id)){
            Number = jpaNumberRepository.findById(id).get();
            System.out.println(Number.toString());
        }
        return Number;
    }
}
