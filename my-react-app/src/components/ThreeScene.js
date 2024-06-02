import React, { useEffect, useRef } from 'react';
import * as THREE from 'three';

const ThreeScene = () => {
  const mountRef = useRef(null);

  useEffect(() => {
    // Store the current value of mountRef in a local variable
    const currentMount = mountRef.current;

    // Set up the scene, camera, and renderer
    const scene = new THREE.Scene();
    const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
    const renderer = new THREE.WebGLRenderer();
    renderer.setSize(window.innerWidth, window.innerHeight);
    currentMount.appendChild(renderer.domElement);

    // Create materials with different colors
    const materials = [
      new THREE.MeshBasicMaterial({ color: 0xff0000 }), // Red
      new THREE.MeshBasicMaterial({ color: 0x00ff00 }), // Green
      new THREE.MeshBasicMaterial({ color: 0x0000ff }), // Blue
      new THREE.MeshBasicMaterial({ color: 0xffff00 }), // Yellow
      new THREE.MeshBasicMaterial({ color: 0xff00ff }), // Magenta
      new THREE.MeshBasicMaterial({ color: 0x00ffff })  // Cyan
    ];

    // Create a cube with different materials for each face
    const geometry = new THREE.BoxGeometry();
    const cube = new THREE.Mesh(geometry, materials);
    scene.add(cube);

    camera.position.z = 5;

    // Animation loop
    const animate = () => {
      requestAnimationFrame(animate);
      cube.rotation.x += 0.01;
      cube.rotation.y += 0.01;
      renderer.render(scene, camera);
    };
    animate();

    // Cleanup on component unmount
    return () => {
      currentMount.removeChild(renderer.domElement);
    };
  }, []);

  return <div ref={mountRef} />;
};

export default ThreeScene;
