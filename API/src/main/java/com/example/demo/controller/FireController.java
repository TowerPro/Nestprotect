package com.example.demo.controller;

import com.example.demo.bean.Fire;
import com.example.demo.result.ResultModel;
import com.example.demo.result.ResultModelTool;
import com.example.demo.service.IFireService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

@RestController
@RequestMapping(value = "/Fires")
public class FireController {


    @Autowired
    IFireService FireService;
    @RequestMapping(value = "/last",method = RequestMethod.GET)
    public ResultModel getLastFire(){
        Fire newLastFire  = FireService.getLastFire();
        ResultModel resultModel = new ResultModel();
        resultModel.setCode(0);
        resultModel.setData(newLastFire);
        return ResultModelTool.handleResultModel(resultModel);
    }

    @RequestMapping(value = "/all",method = RequestMethod.GET)
    public ResultModel getAllFire(){
        List<Fire> FireList = FireService.getAllFire();
        Map<String,List<Fire>> FireMap = new HashMap<>();
        if (FireList!=null){
            FireMap.put("Fires",FireList);
        }
        ResultModel resultModel = new ResultModel();
        resultModel.setCode(0);
        resultModel.setData(FireMap);
        return ResultModelTool.handleResultModel(resultModel);
    }

    @PostMapping(value = "/addFire")
    public ResultModel addFire(@RequestParam long uid, @RequestParam String date,@RequestParam String time){
        Fire Fire = new Fire(uid,date,time);
        int errorCode = FireService.addFire(Fire);
        ResultModel resultModel = new ResultModel();
        resultModel.setCode(errorCode);
        resultModel.setData(Fire);
        return ResultModelTool.handleResultModel(resultModel);
    }

    @PostMapping(value = "/updateFire")
    public ResultModel updateFire(@RequestParam long uid, @RequestParam String date,@RequestParam String time){
        Fire Fire = new Fire(uid,date,time);
        int errorCode = FireService.updateFire(Fire);
        ResultModel resultModel = new ResultModel();
        resultModel.setCode(errorCode);
        resultModel.setData(Fire);
        return ResultModelTool.handleResultModel(resultModel);
    }
    @GetMapping(value = "/deleteFire/{num}")
    public ResultModel deleteFire(@PathVariable long num){
        int errorCode = FireService.deleteFire(num);
        ResultModel resultModel = new ResultModel();
        resultModel.setCode(errorCode);
        List<Fire> FireList = FireService.getAllFire();
        Map<String,List<Fire>> FireMap = new HashMap<>();
        if (FireList!=null){
            FireMap.put("Fires",FireList);
        }
        resultModel.setData(FireMap);
        return ResultModelTool.handleResultModel(resultModel);
    }
}

