package com.example.demo.result;

import java.util.HashMap;
import java.util.Map;

public class ResultModelTool {

    public static ResultModel handleResultModel(ResultModel resultModel) {

        ResultModel handledModel = new ResultModel();
        Map map = new HashMap();
        if (resultModel != null) {
            int error = resultModel.getCode();
            handledModel.setCode(error);
            switch (error) {
                case 10000:
                    handledModel.setMsg("网络繁忙,请稍后重试");
                    handledModel.setData(map);
                    break;
                case 10001:
                    handledModel.setMsg("无此用户");
                    handledModel.setData(map);
                    break;
                case 10002:
                    handledModel.setMsg("添加成功");
                    handledModel.setData(resultModel.getData());
                    break;
                case 10003:
                    handledModel.setMsg("删除成功");
                    handledModel.setData(resultModel.getData());
                    break;
                case 10004:
                    handledModel.setMsg("更新成功");
                    handledModel.setData(resultModel.getData());
                    break;
                case -1:
                    handledModel.setMsg("请求失败");
                    handledModel.setData(map);
                    break;
                case 10005:
                    handledModel.setMsg("此用户已存在");
                    handledModel.setData(map);
                    break;
                case 10006:
                    handledModel.setMsg("添加失败");
                    handledModel.setData(map);
                    break;
                case 10007:
                    handledModel.setMsg("删除失败");
                    handledModel.setData(map);
                    break;
                case 10008:
                    handledModel.setMsg("更新失败");
                    handledModel.setData(map);
                    break;
                default:
                    handledModel.setMsg("请求成功");
                    handledModel.setData(resultModel.getData());
                    break;
            }
        }
        return handledModel;
    }
}


