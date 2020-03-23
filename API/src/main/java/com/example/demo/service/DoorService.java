package com.example.demo.service;

import com.example.demo.bean.Door;
import com.example.demo.repository.JpaDoorRepository;
import com.example.demo.result.ErrorCode;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;
import org.springframework.stereotype.Service;


import javax.annotation.Resource;
import java.util.List;

@Service
public class DoorService implements IDoorService {

    @Autowired
    JpaDoorRepository jpaDoorRepository;

    @Override
    public Door getLastDoor() {
        List<Door> Doors = jpaDoorRepository.findAll();
        System.out.println(Doors.toString());
        Door lastDoor;
        System.out.println(Doors.size());
        int num;
        num = Doors.size();
        lastDoor = Doors.get(num-1);
        System.out.println(lastDoor);
        return lastDoor;
    }
    @Override
    public List<Door> getAllDoor() {
        List<Door> Doors = jpaDoorRepository.findAll();
        System.out.println(Doors.toString());
        return Doors;
    }

    @Override
    public int addDoor(Door Door) {
        if (jpaDoorRepository.existsById(Door.getId())){
            System.out.println("Door  is existed");
            return ErrorCode.EXISTUSER;
        }
        Door saveDoor = jpaDoorRepository.save(Door);
        if (saveDoor != null && saveDoor.getId() == Door.getId()) {
            System.out.println("save success");
            return ErrorCode.ADDSUCCESS;
        } else {
            System.out.println("save failure");
            return ErrorCode.ADDFAIL;
        }
    }

    @Override
    public int deleteDoor(long id) {
        if (jpaDoorRepository.existsById(id)) {
            jpaDoorRepository.deleteById(id);
            System.out.println("删除成功");
            return ErrorCode.DELETESUCCESS;
        }
        System.out.println("删除失败");
        return ErrorCode.NOTEXISTUSER;
    }

    @Override
    public int updateDoor(Door Door) {
        if (jpaDoorRepository.existsById(Door.getId())){
            jpaDoorRepository.save(Door);
            System.out.println("更新成功");
            return ErrorCode.UPDATESUCCESS;
        }
        System.out.println("更新失败");
        return ErrorCode.UPDATEFAIL;
    }

    @Override
    public Door queryDoor(long id) {
        Door Door = null;
        if (jpaDoorRepository.existsById(id)){
            Door = jpaDoorRepository.findById(id).get();
            System.out.println(Door.toString());
        }
        return Door;
    }
}
