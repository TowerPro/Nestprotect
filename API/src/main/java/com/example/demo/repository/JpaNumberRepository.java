package com.example.demo.repository;

import com.example.demo.bean.Number;
import org.springframework.data.jpa.repository.JpaRepository;

public interface JpaNumberRepository extends JpaRepository<Number,Long> {
}

