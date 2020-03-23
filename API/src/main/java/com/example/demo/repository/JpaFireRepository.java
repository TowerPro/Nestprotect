package com.example.demo.repository;

import com.example.demo.bean.Fire;
import org.springframework.data.jpa.repository.JpaRepository;

public interface JpaFireRepository extends JpaRepository<Fire,Long> {
}

