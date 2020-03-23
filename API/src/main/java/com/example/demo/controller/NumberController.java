package com.example.demo.controller;

import com.example.demo.bean.Number;
import com.example.demo.result.ResultModel;
import com.example.demo.result.ResultModelTool;
import com.example.demo.service.INumberService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

@RestController
@RequestMapping(value = "/Numbers")
public class NumberController {


    @Autowired
    INumberService NumberService;
    @RequestMapping(value = "/last",method = RequestMethod.GET)
    public ResultModel getLastNumber(){
        Number newLastNumber  = NumberService.getLastNumber();
        ResultModel resultModel = new ResultModel();
        resultModel.setCode(0);
        resultModel.setData(newLastNumber);
        return ResultModelTool.handleResultModel(resultModel);
    }

    @RequestMapping(value = "/all",method = RequestMethod.GET)
    public ResultModel getAllNumber(){
        List<Number> NumberList = NumberService.getAllNumber();
        Map<String,List<Number>> NumberMap = new HashMap<>();
        if (NumberList!=null){
            NumberMap.put("Numbers",NumberList);
        }
        ResultModel resultModel = new ResultModel();
        resultModel.setCode(0);
        resultModel.setData(NumberMap);
        return ResultModelTool.handleResultModel(resultModel);
    }

    @PostMapping(value = "/addNumber")
    public ResultModel addNumber(@RequestParam long uid, @RequestParam String date,@RequestParam String time,@RequestParam String peoplenum){
        Number Number = new Number(uid,date,time,peoplenum);
        int errorCode = NumberService.addNumber(Number);
        ResultModel resultModel = new ResultModel();
        resultModel.setCode(errorCode);
        resultModel.setData(Number);
        return ResultModelTool.handleResultModel(resultModel);
    }

    @PostMapping(value = "/updateNumber")
    public ResultModel updateNumber(@RequestParam long uid, @RequestParam String date,@RequestParam String time,@RequestParam String peoplenum){
        Number Number = new Number(uid,date,time,peoplenum);
        int errorCode = NumberService.updateNumber(Number);
        ResultModel resultModel = new ResultModel();
        resultModel.setCode(errorCode);
        resultModel.setData(Number);
        return ResultModelTool.handleResultModel(resultModel);
    }
    @GetMapping(value = "/deleteNumber/{num}")
    public ResultModel deleteNumber(@PathVariable long num){
        int errorCode = NumberService.deleteNumber(num);
        ResultModel resultModel = new ResultModel();
        resultModel.setCode(errorCode);
        List<Number> NumberList = NumberService.getAllNumber();
        Map<String,List<Number>> NumberMap = new HashMap<>();
        if (NumberList!=null){
            NumberMap.put("Numbers",NumberList);
        }
        resultModel.setData(NumberMap);
        return ResultModelTool.handleResultModel(resultModel);
    }
}

