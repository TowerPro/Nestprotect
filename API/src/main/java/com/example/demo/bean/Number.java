package com.example.demo.bean;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name = "people")
public class Number {
    @Id
    private long uid;
    @Column(name = "date")
    private String date;
    @Column(name = "time")
    private String time;
    @Column(name = "peoplenum")
    private String peoplenum;

    public Number() {
    }

    public Number(long uid,String date, String time,String peoplenum) {
        this.uid = uid;
        this.date = date;
        this.time = time;
        this.peoplenum = peoplenum;
    }

    public long getUid() {
        return uid;
    }

    public void setUid(long uid) {
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
    public void setPeoplenum(String peoplenum){
        this.peoplenum = peoplenum;
    }
    public String getPeoplenum(){
        return peoplenum;
    }
}