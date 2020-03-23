package com.example.demo.controller;

import com.example.demo.bean.Door;
import com.example.demo.result.ResultModel;
import com.example.demo.result.ResultModelTool;
import com.example.demo.service.IDoorService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

@RestController
@RequestMapping(value = "/Doors")
public class DoorController {


    @Autowired
    IDoorService DoorService;
    @RequestMapping(value = "/last",method = RequestMethod.GET)
    public ResultModel getLastDoor(){
        Door newLastDoor  = DoorService.getLastDoor();
        ResultModel resultModel = new ResultModel();
        resultModel.setCode(0);
        resultModel.setData(newLastDoor);
        return ResultModelTool.handleResultModel(resultModel);
    }

    @RequestMapping(value = "/all",method = RequestMethod.GET)
    public ResultModel getAllDoor(){
        List<Door> DoorList = DoorService.getAllDoor();
        Map<String,List<Door>> DoorMap = new HashMap<>();
        if (DoorList!=null){
            DoorMap.put("Doors",DoorList);
        }
        ResultModel resultModel = new ResultModel();
        resultModel.setCode(0);
        resultModel.setData(DoorMap);
        return ResultModelTool.handleResultModel(resultModel);
    }

    @PostMapping(value = "/addDoor")
    public ResultModel addDoor(@RequestParam long uid, @RequestParam String date,@RequestParam String time){
        Door Door = new Door(uid,date,time);
        int errorCode = DoorService.addDoor(Door);
        ResultModel resultModel = new ResultModel();
        resultModel.setCode(errorCode);
        resultModel.setData(Door);
        return ResultModelTool.handleResultModel(resultModel);
    }

    @PostMapping(value = "/updateDoor")
    public ResultModel updateDoor(@RequestParam long uid, @RequestParam String date,@RequestParam String time){
        Door Door = new Door(uid,date,time);
        int errorCode = DoorService.updateDoor(Door);
        ResultModel resultModel = new ResultModel();
        resultModel.setCode(errorCode);
        resultModel.setData(Door);
        return ResultModelTool.handleResultModel(resultModel);
    }
    @GetMapping(value = "/deleteDoor/{num}")
    public ResultModel deleteDoor(@PathVariable long num){
        int errorCode = DoorService.deleteDoor(num);
        ResultModel resultModel = new ResultModel();
        resultModel.setCode(errorCode);
        List<Door> DoorList = DoorService.getAllDoor();
        Map<String,List<Door>> DoorMap = new HashMap<>();
        if (DoorList!=null){
            DoorMap.put("Doors",DoorList);
        }
        resultModel.setData(DoorMap);
        return ResultModelTool.handleResultModel(resultModel);
    }
}

