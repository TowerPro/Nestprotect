package com.example.demo.bean;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name = "fire")
public class Fire {
    @Id
    private long uid;
    @Column(name = "date")
    private String date;
    @Column(name = "time")
    private String time;

    public Fire() {
    }

    public Fire(long uid,String date, String time) {
        this.uid = uid;
        this.date = date;
        this.time = time;
    }

    public long getId() {
        return uid;
    }

    public void setId(long uid) {
        this.uid = uid;
    }

    public  String getTime(){
        return time;
    }

    public void setTime(String time){
        this.time = time;
    }

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }
}