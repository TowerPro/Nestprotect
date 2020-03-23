package com.example.demo.repository;

import com.example.demo.bean.Door;
import org.springframework.data.jpa.repository.JpaRepository;

public interface JpaDoorRepository extends JpaRepository<Door,Long> {
}

